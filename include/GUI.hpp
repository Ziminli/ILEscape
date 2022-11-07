# pragma once

#include <Global.hpp>

using namespace std;


class Image {
    public:
        /* Constructor */
        Image(sf::RenderWindow& window, string filename);

        // display the image
        void drawImg(int xPos = 0, int yPos = 0, 
            float x_scale = 1, float y_scale = 1, 
            int width = WINDOW_WIDTH, int height = WINDOW_HEIGHT,
            unsigned char imgOpacity = 160, unsigned char maskOpacity = MASK_OPACITY, float angle = 0);

    protected:
        /* Variables / Attributes */
        sf::RenderWindow& window;
        string filename;
        string path = ASSET_PATH;

        sf::Vector2u size;
        sf::Texture texture;
        sf::RectangleShape mask;

        /* Protected Methods */
        sf::Texture getTexture();
        
};


class Button {
    public:
        /* Constructor */
        Button(sf::RenderWindow& window, int xPos, int yPos, int width = BUTTON_WIDTH, int height = BUTTON_HEIGHT);

        void drawButton();

        inline void setFillColor(sf::Color newColor) {
            fillColor = newColor;
        };

        inline void setOutlineColor(sf::Color newColor) {
            outlineColor = newColor;
        };

        inline void setOutlineThickness(int newThickness) {
            outlineThickness = newThickness;
        };

        bool checkBounds(sf::Vector2i mousePos);

    protected:
        /* Variables / Attributes */
        sf::RenderWindow& window;
        sf::Vector2f position;
        sf::Color fillColor = sf::Color::White;
        sf::Color outlineColor = sf::Color::Black;
        short outlineThickness = BUTTON_OUTLINE_THICKNESS;
        int width;
        int height;

        /* Private Methods */
};


class Text {
    public:
        /* Constructor */
        Text(sf::RenderWindow& window, string fontName, string textContent="", unsigned short charSize = 50);

        void drawText(int xPos = 0, int yPos = 0, 
            unsigned char r = 255, unsigned char g = 255, unsigned char b = 255, 
            unsigned char opacity = 255);

        bool drawAnimatedText(sf::Clock clock, bool& finish, 
            int xPos = 0, int yPos = 0, 
            unsigned char r = 255, unsigned char g = 255, unsigned char b = 255, 
            unsigned char opacity = 255);

        inline void changeText(string newText) {
            textContent = newText;
        };

        inline void changeLineSpace(float newLineSpace) {
            lineSpace = newLineSpace;
        };

        inline void changeLetterSpace(float newLetterSpace) {
            letterSpace = newLetterSpace;
        };  

    protected:
        /* Variables / Attributes */
        sf::RenderWindow& window;
        string fontName;
        string path = FONT_PATH;
        string textContent;
        unsigned short charSize;
        float lineSpace = 1;
        float letterSpace = 1;

        /* Private Methods */
        
};


string toLowerCase(string str);


class Tool : public Image {
    public:
        // Constructor
        Tool(sf::RenderWindow& window, string filename, short ToolID);

        // Setters
        inline void setXPos(int newXPos) {
            xPos = newXPos;
        }

        inline void setYPos(int newYPos) {
            yPos = newYPos;
        }

        inline void setShow(bool value) {
            show = value;
        }

        void setStatus(short newStatus);

        // Getter
        inline bool getShow() {
            return show;
        }

        inline short getID() {
            return id;
        }

        inline short getStatus() {
            return status;
        }

        // display the visual of the tool
        void drawImg(float angle = 0);
        void drawImg(float xScale, float yScale, float angle = 0);

    private:
        /* Variables / Attributes */
        short id;
        short xPos = 0;
        short yPos = 0;
        bool show = false;
        short status = 0;    // 0: inactive; 1: active in inventory; 2: active on workbench

};


class Inventory {
    public:
        Inventory(sf::RenderWindow& window, int xPos, int yPos);

        void drawInventory();

        // Get inventory choice
        int checkBounds(sf::Vector2i mousePos);

        // Check if has a tool
        inline bool checkHasTool(int id){
            return findTool(id) == -1 ? false : true;
        };

        // Find the storage index of a tool (-1 returned if does not exist)
        short findTool(int id);

        Tool* retrieveTool(int idx);

        bool storeTool(int toolID, Tool* toolPtr);

        void removeTool(Tool* tempToolPtr);

        // Get all wandering tools back
        void collectBackTools();


    private:
        /* Variables / Attributes */
        sf::RenderWindow& window;
        sf::Vector2f position;

        //char size = 0;
        unsigned short width = INVENTORY_BLOCK_WIDTH;
        unsigned short height = INVENTORY_BLOCK_HEIGHT;

        map<int, sf::RectangleShape> inventory_struct;      // Inventory structure
        vector<int> storedItems = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
        vector<Tool*> storedItemsPtr = {nullptr, nullptr, nullptr, nullptr, 
            nullptr, nullptr, nullptr, nullptr, nullptr, nullptr};
        char capacity = 0;

        /* Private Methods */
        
};


void drawInventoryTool(sf::RenderWindow& window, Inventory inventory, Tool* tool, Tool* tempToolPtr, bool dragging);


class DialogBox : public Button, public Text {
    public:
        // Constructor
        DialogBox(sf::RenderWindow& window, char mode, 
        string textContent="", int xPos = 0, int yPos = 0, string fontName="AndadaPro-Italic_wght.ttf",
        unsigned short charSize = 50, int width = BUTTON_WIDTH, int height = BUTTON_HEIGHT);

        // Draw Dialog Box
        void drawDialogBox();
        void drawDialogBox(sf::Clock clock, bool& finish);

        // Setters
        inline void setTextContent(string newText) {
            this->textContent = newText;
        };

        inline void appendTextContent(string newText) {
            this->textContent.append(newText);
        };

        inline void setTextXPos(short newXPos) {
            this->textXPos = newXPos;
        };

        // Getters
        inline string getTextContent() const {
            return this->textContent;
        };

        inline short getTextContentSize() const {
            return this->textContent.size();
        };


    private:   
        short textXPos;
        short textYPos;
        sf::Color textColor = sf::Color::White;
        char mode;

};


class KeyPad : public Image{
    public:
        KeyPad(sf::RenderWindow& window, string password);

        // Drawing Functions
        void drawImg();
        void drawKeyPad();

        // Check Cancel Button clicks
        bool checkCancelBounds(sf::Vector2i mousePos);

        // Restore the puzzle
        void restorePuzzle();

        // Check user input size, comparing to the password size
        bool checkInputSize();

        // Store User Input
        void storeUserInput(sf::Event& event);

        // Set Message
        inline void setMessage() {
            this->messageBox.setTextContent("Invalid Password!");
        }

        // Check if the input matches the password
        inline bool checkPasswordMatch() {
            return this->digitalDisplay.getTextContent() == password ? true : false;
        }

    private:      
        short xPos = KEYPAD_XPOS;
        short yPos = KEYPAD_YPOS;

        string password;
        unsigned short passwordSize;

        DialogBox cancelButton = DialogBox(window, 2, "Cancel", CANCEL_XPOS, CANCEL_YPOS);
        DialogBox digitalDisplay = DialogBox(window, 3, "", DISPLAY_XPOS, DISPLAY_YPOS);
        DialogBox messageBox = DialogBox(window, 4, "", MESSAGE_XPOS, MESSAGE_YPOS);

};



class Workbench : public Button, public Image {
    public:
        Workbench(sf::RenderWindow& window, short numParts = NUMBER_OF_ASSEMBLING_PARTS,
            int xPos = WORKBENCH_XPOS, int yPos = WORKBENCH_YPOS, 
            int width = WORKBENCH_WIDTH, int height = WORKBENCH_HEIGHT);

        // Draw Workbench
        void drawImg();
        void drawWorkbench(bool readyAssemble);

        bool checkCloseBounds(sf::Vector2i mousePos);
        bool checkAssembleBounds(sf::Vector2i mousePos);
        void addTool(short id);
        bool checkToolComplete();

        inline void clearTools() {
            placedTools.clear();
        }

    private:
        sf::RenderWindow& window;
        DialogBox closeButton = DialogBox(window, 5, "X", WORKBENCH_CLOSE_BUTTON_XPOS, WORKBENCH_CLOSE_BUTTON_YPOS);
        DialogBox assembleButton = DialogBox(window, 2, "Assemble", 
            WORKBENCH_ASSEMBLE_BUTTON_XPOS, WORKBENCH_ASSEMBLE_BUTTON_YPOS);
            
        unsigned short numParts;    // Number of tools that is needed to enable assembly
        set<int> placedTools;    // The tools that are currently on workbench 

};

