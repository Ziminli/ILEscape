#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <SFML/Graphics.hpp>

#include "Global.hpp"
#include "GUI.hpp"

using namespace std;

/* ---------------------------------- */
/* ---------- Image Class ----------- */
/* ---------------------------------- */

Image::Image(sf::RenderWindow& window, string filename) : window(window), filename(filename) {
    texture = getTexture();
    size = texture.getSize();
}

sf::Texture Image::getTexture() {
    sf::Texture texture;
    if (!texture.loadFromFile(path + filename)) {
        cerr << "Error! Image cannot be opened!" << endl;
        system("pause");
        exit(1);
    }
    return texture;
};

void Image::drawImg(int xPos /*= 0*/, int yPos /*= 0*/, 
    float x_scale /*= 1*/, float y_scale /*= 1*/, 
    int width /*=WINDOW_WIDTH */, int height /*= WINDOW_HEIGHT */,
    unsigned char imgOpacity /*= 160*/, unsigned char maskOpacity /*=MASK_OPACITY*/,
    float angle /*= 0*/) {

    sf::Sprite image;

    image.setTexture(texture);
    image.setPosition(xPos,yPos);
    image.scale(x_scale*static_cast<float>(width)/size.x, y_scale*static_cast<float>(height)/size.y);
    image.setColor(sf::Color(255,255,255,imgOpacity));
    image.setRotation(angle);

    mask.setFillColor(sf::Color(255,255,255,maskOpacity));
    mask.setSize(sf::Vector2f(width, height));

    window.draw(image);
    window.draw(mask);
};

/* ---------------------------------- */
/* ---------- Button Class ---------- */
/* ---------------------------------- */

Button::Button(sf::RenderWindow& window, int xPos, int yPos, int width, int height)
    : window(window), position(xPos, yPos), width(width), height(height) {}

void Button::drawButton() {
    sf::RectangleShape button;
    
    button.setSize(sf::Vector2f(width, height));
    button.setFillColor(fillColor);
    button.setPosition(position);
    button.setOutlineColor(outlineColor);
    button.setOutlineThickness(outlineThickness);

    window.draw(button);
};

bool Button::checkBounds(sf::Vector2i mousePos) {
    int mouseX = mousePos.x, mouseY = mousePos.y;

    if (mouseX < position.x || mouseX > position.x + width) {
        return false;
    }
    else if (mouseY < position.y || mouseY > position.y + height) {
        return false;
    }
    return true;
}


/* ---------------------------------------- */
/* ------------- Text Class --------------- */
/* ---------------------------------------- */

Text::Text(sf::RenderWindow& window, string fontName, string textContent, unsigned short charSize)
    : window(window), fontName(fontName), textContent(textContent), charSize(charSize) {}


void Text::drawText(int xPos /*= 0*/, int yPos /*= 0*/,
    unsigned char r /*= 255*/, unsigned char g /*= 255*/, unsigned char b /*= 255*/, 
    unsigned char opacity /*= 255*/) {

    sf::Font font;
    if (!font.loadFromFile(path + fontName)) {
        cerr << "Error! Fonts cannot be loaded!" << endl; 
        system("pause");
        exit(1);
    }

    sf::Text text;
    text.setFont(font);
    text.setPosition(xPos, yPos);
    text.setFillColor(sf::Color(r,g,b,opacity));
    text.setCharacterSize(charSize);
    text.setLineSpacing(lineSpace);
    text.setString(textContent);
    text.setLetterSpacing(letterSpace);

    window.draw(text);
};


bool Text::drawAnimatedText(sf::Clock clock, bool& finish, int xPos /*= 0*/, int yPos /*= 0*/,
    unsigned char r /*= 255*/, unsigned char g /*= 255*/, unsigned char b /*= 255*/, 
    unsigned char opacity /*= 255*/) {

    sf::Font font;
    if (!font.loadFromFile(path + fontName)) {
        cerr << "Error! Fonts cannot be loaded!" << endl; 
        system("pause");
    }

    sf::Text text;
    text.setFont(font);
    text.setPosition(xPos, yPos);
    text.setFillColor(sf::Color(r,g,b,opacity));
    text.setCharacterSize(charSize);
    text.setLineSpacing(lineSpace);
    text.setLetterSpacing(letterSpace);

    if (!finish) {
        sf::Time time = clock.getElapsedTime();
        short idx = static_cast<short>(time.asMilliseconds() / SLEEP_TIME);

        if (idx < textContent.size()) {
            text.setString(textContent.substr(0,idx));
            window.draw(text);
            return false;
        }
        else {
            text.setString(textContent);
            window.draw(text);
            finish = true;
            return true;
        } 
    }
    else {
        text.setString(textContent);
        window.draw(text);
        finish = true;
        return true;
    }
};


string toLowerCase(string str) {
    if (str.empty()) {
        return str;
    }
    for (string::iterator it = str.begin(); it != str.end(); it++) {
        if (isalpha(*it)) {
            *it = tolower(*it);
        }
    }
    return str;
};


/* --------------------------------------- */
/* ---------------- Tool ----------------- */
/* --------------------------------------- */

Tool::Tool(sf::RenderWindow& window, string filename, short ToolID) : Image(window,filename), id(ToolID) {}


void Tool::setStatus(short newStatus) {
    if (status == 1 && newStatus == 2) {
        this->size.x = size.x/newStatus;
        this->size.y = size.y/newStatus;
    }
    else if (status == 2 && newStatus == 1) {
        this->size.x = size.x*status;
        this->size.y = size.y*status;
    }
    else if (newStatus == 0) {
        this->size = texture.getSize();
    }
    status = newStatus;
};


void Tool::drawImg(float angle /* =0 */) {

    sf::Sprite visual;
    texture.setSmooth(true);

    visual.setTexture(texture);
    visual.setPosition(xPos, yPos);
    visual.scale(static_cast<float>(TOOL_WIDTH-INVENTORY_OUTLINE_THICKNESS)/size.x, 
                static_cast<float>(TOOL_HEIGHT-INVENTORY_OUTLINE_THICKNESS)/size.y);
    visual.setRotation(angle);

    window.draw(visual);
            
};


void Tool::drawImg(float xScale, float yScale, float angle /* =0 */) {

    sf::Sprite visual;
    texture.setSmooth(true);

    visual.setTexture(texture);
    visual.setPosition(xPos, yPos);
    visual.scale(xScale/size.x, yScale/size.y);
    visual.setRotation(angle);

    window.draw(visual);
            
};

/* --------------------------------------- */
/* ------------- Inventory --------------- */
/* --------------------------------------- */

Inventory::Inventory(sf::RenderWindow& window, int xPos, int yPos)
    : window(window), position(xPos, yPos) {
        for (int i = 0; i < INVENTORY_SLOTS; i++) {
            sf::RectangleShape inventory_block;
            inventory_struct.insert({i, inventory_block});
        }   
    }


void Inventory::drawInventory() {
    for (auto block : inventory_struct) {
        block.second.setSize(sf::Vector2f(width, height));
        block.second.setPosition(position.x+block.first*INVENTORY_BLOCK_WIDTH, position.y);
        block.second.setFillColor(sf::Color(255,255,255,20));
        block.second.setOutlineColor(sf::Color(166,166,166));
        block.second.setOutlineThickness(INVENTORY_OUTLINE_THICKNESS);

        window.draw(block.second);
    }
};


int Inventory::checkBounds(sf::Vector2i mousePos) {
    int mouseX = mousePos.x, mouseY = mousePos.y;

    if (mouseX < position.x || mouseX > position.x + INVENTORY_SLOTS*width) {
        return -1;
    }
    else if (mouseY < position.y || mouseY > position.y + height) {
        return -1;
    }
    else {
        return static_cast<int>((mouseX - position.x) / width); 
    }
};


short Inventory::findTool(int id) {
    vector<int>::iterator it = find(storedItems.begin(), storedItems.end(), id);
    return it != storedItems.end() ? distance(storedItems.begin(), it) : -1;
};  



bool Inventory::storeTool(int toolID, Tool* toolPtr) {
    if (capacity < INVENTORY_SLOTS) {
        vector<int>::iterator it = find(storedItems.begin(), storedItems.end(), -1);
        storedItems.at(it-storedItems.begin()) = toolID;
        storedItemsPtr.at(it-storedItems.begin()) = toolPtr;
        toolPtr->setXPos(INVENTORY_POS_X+capacity*INVENTORY_BLOCK_WIDTH+INVENTORY_OUTLINE_THICKNESS/2);
        toolPtr->setYPos(INVENTORY_BLOCK_HEIGHT);
        toolPtr->setStatus(1);
        capacity++;
        return true;
    }
    return false;
};


Tool* Inventory::retrieveTool(int idx) {
    if (idx < 0 || idx > this->storedItems.size()) {
        return nullptr;
    }
    else if (storedItems.at(idx) != -1) {
        return storedItemsPtr.at(idx);
    }
    return nullptr;
};


void Inventory::removeTool(Tool* tempToolPtr) {
    short id = tempToolPtr->getID();
    vector<int>::iterator it = find(storedItems.begin(), storedItems.end(), id);
    
    if (it != storedItems.end()) {
        char idx = distance(storedItems.begin(), it);

        storedItems.at(idx) = -1;
        storedItemsPtr.at(idx)->setShow(false);
        storedItemsPtr.at(idx)->setStatus(0);
        storedItemsPtr.at(idx) = nullptr;
        //storedItemsPtr.erase(storedItemsPtr.begin()+idx);
        capacity--;

        tempToolPtr = nullptr;
    }
};


void Inventory::collectBackTools() {
    for (int i = 0; i < 10; i++) {
        if (this->storedItems.at(i) != -1)
            this->storedItemsPtr.at(i)->setStatus(1);
    }
};      


// Draw inventory tools within the window
void drawInventoryTool(sf::RenderWindow& window, Inventory inventory, Tool* tool, Tool* tempToolPtr, bool dragging) {
    if (inventory.checkHasTool(tool->getID())) {
        if (tempToolPtr == tool && dragging && tool->getStatus() == 1) {
            sf::Vector2i position = sf::Mouse::getPosition(window);
            tool->setXPos(position.x-TOOL_WIDTH/2);
            tool->setYPos(position.y-TOOL_HEIGHT/2);
        }
        else if (!dragging && tool->getStatus() == 1) {
            tool->setXPos(INVENTORY_POS_X+inventory.findTool(tool->getID())*INVENTORY_BLOCK_WIDTH);
            tool->setYPos(INVENTORY_POS_Y);
        }
        tool->drawImg();
    }

};


/* -------------------------------------------- */
/* --------------- Dialog Box ----------------- */
/* -------------------------------------------- */

DialogBox::DialogBox(sf::RenderWindow& window, char mode,
    string textContent /* = "" */, int xPos /* = 0 */, int yPos /* = 0 */, 
    string fontName /* ="AndadaPro-Italic_wght.ttf"*/, unsigned short charSize /* = 50 */, 
    int width /*= BUTTON_WIDTH*/, int height /*= BUTTON_HEIGHT*/) 
    : Text(window, fontName, textContent, charSize), Button(window, xPos, yPos, width, height), mode(mode) {

        switch(mode) {
            // Backstory Box
            case 0:
                this->charSize = 40;
                this->width = BACKSTORY_BOX_WIDTH;
                this->height = BACKSTORY_BOX_HEIGHT;
                this->position = sf::Vector2f(0, WINDOW_HEIGHT-this->height);
                this->textXPos = this->position.x + 50;
                this->textYPos = this->position.y + 50;
                this->fillColor = sf::Color(0, 0, 0, 200);
                this->lineSpace = 1.2;
                this->letterSpace = 1.2;
                break;

            // Interactive Box
            case 1:
                this->charSize = 25;
                this->width = INTERACT_BOX_WIDTH;
                this->height = INTERACT_BOX_HEIGHT;
                this->textXPos = this->position.x + 15;
                this->textYPos = this->position.y + 15;
                this->fillColor = sf::Color(0, 0, 0, 120);
                this->textColor = sf::Color(220, 220, 220, 250);
                this->fontName = "/Andada_Pro/static/AndadaPro-Bold.ttf";
                break;

            // Keypad Button
            case 2: 
                this->charSize = 40;
                this->width = CANCEL_WIDTH;
                this->height = CANCEL_HEIGHT;
                this->textXPos = this->position.x + 73;
                this->textYPos = this->position.y + 20;
                this->fillColor = sf::Color(68, 68, 68, 255);
                this->textColor = sf::Color(220, 220, 220, 250);
                this->setOutlineColor(sf::Color::White);
                this->setOutlineThickness(-1);
                break;

            // Keypad Display
            case 3:
                this->charSize = 100;
                this->width = DISPLAY_WIDTH;
                this->height = DISPLAY_HEIGHT;
                this->textXPos = this->position.x + 15;
                this->textYPos = this->position.y - 10;
                this->fillColor = sf::Color(65, 66, 66, 255);
                this->textColor = sf::Color(212, 235, 255, 250);
                this->setOutlineColor(sf::Color::Black);
                this->setOutlineThickness(-2);
                this->fontName = "/digital/digital-7 (italic).ttf";
                break;

            // Keypad Message
            case 4:
                this->charSize = 32;
                this->width = DISPLAY_WIDTH;
                this->height = DISPLAY_HEIGHT;
                this->textXPos = this->position.x + 15;
                this->textYPos = this->position.y + 40;
                this->fillColor = sf::Color(68, 68, 68, 255);
                this->textColor = sf::Color(220, 220, 220, 250);
                this->setOutlineColor(sf::Color::Transparent);
                this->changeLetterSpace(1.8);
                break;

            // Workshop Close Button
            case 5:
                this->charSize = 58;
                this->width = WORKBENCH_CLOSE_BUTTON_WIDTH;
                this->height = WORKBENCH_CLOSE_BUTTON_HEIGHT;
                this->textXPos = this->position.x - 5;
                this->textYPos = this->position.y;
                this->fillColor = sf::Color(68, 68, 68, 200);
                this->textColor = sf::Color(255,255,255,140);
                this->setOutlineColor(sf::Color::Black);
                this->setOutlineThickness(-3);
                this->fontName = "ErikGCapsSketches.ttf";
                break;


            default:
                // cout << "default box" << endl;
                this->textXPos = this->position.x + 0.1*this->width;
                this->textYPos = this->position.y + 0.1*this->height;
                this->fillColor = sf::Color(0, 0, 0, 200);
                this->textColor = sf::Color(220, 220, 220, 250);
                break;
        }

    };

void DialogBox::drawDialogBox() {
    this->drawButton();
    this->drawText(textXPos, textYPos, textColor.r, textColor.g, textColor.b, textColor.a);
    if (mode == 0) {
        sf::CircleShape triangle(18,3);
        triangle.setFillColor(sf::Color::White);
        triangle.setRotation(90);
        triangle.setPosition(sf::Vector2f(0.96*WINDOW_WIDTH, 0.95*WINDOW_HEIGHT));
        Button::window.draw(triangle);
    }
};


void DialogBox::drawDialogBox(sf::Clock clock, bool& finish) {
    this->drawButton();

    if (this->drawAnimatedText(clock, finish, textXPos, textYPos, textColor.r, textColor.g, textColor.b, textColor.a)) {  
        if (mode == 0) {
            sf::CircleShape triangle(18,3);
            triangle.setFillColor(sf::Color::White);
            triangle.setRotation(90);
            triangle.setPosition(sf::Vector2f(0.96*WINDOW_WIDTH, 0.95*WINDOW_HEIGHT));
            Text::window.draw(triangle);
        }
    }

};


/* -------------------------------------------- */
/* ----------------- KeyPad ------------------- */
/* -------------------------------------------- */

KeyPad::KeyPad(sf::RenderWindow& window, string password) 
    : Image(window, "keypad_0.png"), password(toLowerCase(password)) {
        
    passwordSize = password.size();

    if (passwordSize < 1 || passwordSize > 10) {
        cerr << "Invalid Input Password Length!" << endl;
    }

    if (-3*passwordSize/2+14 >= 1) {
        digitalDisplay.changeLetterSpace(-3*passwordSize/2+14);
    }

    if (passwordSize > 0 && passwordSize < 7) {
        digitalDisplay.setTextXPos(DISPLAY_XPOS + -10*passwordSize+96);
    }
};


void KeyPad::drawImg() {

    sf::Sprite visual;
    texture.setSmooth(true);

    visual.setTexture(texture);
    visual.setPosition(xPos, yPos);
    visual.scale(static_cast<float>(KEYPAD_WIDTH)/size.x, 
                static_cast<float>(KEYPAD_HEIGHT)/size.y);

    window.draw(visual);
};


void KeyPad::drawKeyPad() {
    this->drawImg();
    this->cancelButton.drawDialogBox();
    this->digitalDisplay.drawDialogBox();
    this->messageBox.drawDialogBox();
};


bool KeyPad::checkCancelBounds(sf::Vector2i mousePos) {
    return this->cancelButton.checkBounds(mousePos);
};  


void KeyPad::restorePuzzle() {
    this->digitalDisplay.setTextContent("");
    this->messageBox.setTextContent("");
    this->filename = "keypad_0.png";
    this->texture = getTexture();
};


bool KeyPad::checkInputSize() {
    return this->digitalDisplay.getTextContentSize() <= this->passwordSize ? true : false;
};


void KeyPad::storeUserInput(sf::Event& event) {
    if ((this->digitalDisplay.getTextContentSize() == passwordSize) && event.key.code != sf::Keyboard::BackSpace) {
        return;
    }

    this->messageBox.setTextContent("");

    sf::Keyboard::Key keycode = event.key.code;
    static sf::Keyboard::Key prevKeycode = sf::Keyboard::A;
    string letter;

    if (prevKeycode == sf::Keyboard::LShift || prevKeycode == sf::Keyboard::RShift) {
        switch (keycode)
        {
        case sf::Keyboard::Num2:
            letter = "@";
            break;
        case sf::Keyboard::Num3:
            letter = "#";
            break;
        case sf::Keyboard::Num4:
            letter = "$";
            break;
        case sf::Keyboard::Num5:
            letter = "%";
            break;
        case sf::Keyboard::Slash:
            letter = "?";  
        default:
            break;
        }
    }
    else if (keycode >= sf::Keyboard::Num0 && keycode <= sf::Keyboard::Num9) {
        letter = to_string(keycode - sf::Keyboard::Num0);
    }
    else if (keycode >= sf::Keyboard::Numpad0 && keycode <= sf::Keyboard::Numpad9) {
        letter = to_string(keycode - sf::Keyboard::Numpad0);
    }
    else if (keycode == sf::Keyboard::Space) {
        letter = " ";
    }
    else if (keycode == sf::Keyboard::BackSpace) {
        string currentStr = digitalDisplay.getTextContent();
        currentStr = currentStr.substr(0, currentStr.size()-1);
        this->digitalDisplay.setTextContent(currentStr);

        if ((this->passwordSize % 4 != 0) && (this->digitalDisplay.getTextContentSize() != this->passwordSize)) {
            this->filename = "keypad_0.png";
            this->texture = getTexture();
        }
    }
    else if (keycode >= sf::Keyboard::A && keycode <= sf::Keyboard::Z){
        letter.append(1, keycode - sf::Keyboard::A + 'a');
    }
    else {
        letter = "";
    }

    this->digitalDisplay.appendTextContent(letter);
    prevKeycode = keycode;

    if (this->passwordSize % 4 == 0) {
        this->filename = "keypad_" + 
            to_string(this->digitalDisplay.getTextContentSize()/(this->passwordSize/4)) + ".png";
        this->texture = getTexture();
    }
    else if (this->digitalDisplay.getTextContentSize() == this->passwordSize) {
        this->filename = "keypad_4.png";
        this->texture = getTexture();
    }
};



/* ----------------------------------------------- */
/* ----------------- Workbench ------------------- */
/* ----------------------------------------------- */

Workbench::Workbench(sf::RenderWindow& window, short numParts, int xPos, int yPos, int width, int height) 
    : Image(window, "workbench.jpg"), Button(window, xPos, yPos, width, height), window(window), numParts(numParts) {
    
    this->assembleButton.setTextXPos(WORKBENCH_ASSEMBLE_BUTTON_XPOS+48);
};


void Workbench::drawImg() {

    sf::Sprite visual;
    texture.setSmooth(true);

    visual.setTexture(texture);
    visual.setPosition(position.x, position.y);
    visual.scale(static_cast<float>(WORKBENCH_WIDTH)/size.x, 
                static_cast<float>(WORKBENCH_HEIGHT)/size.y);

    Button::window.draw(visual);
};


void Workbench::drawWorkbench(bool readyAssemble) {
    this->drawImg();
    this->closeButton.drawDialogBox();
    if (readyAssemble)
        this->assembleButton.drawDialogBox();
};


bool Workbench::checkCloseBounds(sf::Vector2i mousePos) {
    return this->closeButton.checkBounds(mousePos);
};


bool Workbench::checkAssembleBounds(sf::Vector2i mousePos) {
    return this->assembleButton.checkBounds(mousePos);
};


void Workbench::addTool(short id) {
    this->placedTools.insert(id);
};  


bool Workbench::checkToolComplete() {
    if (this->placedTools == WORKBENCH_TOOLS) {
        return true;
    }
    return false;
};



