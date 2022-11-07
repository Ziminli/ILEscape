# pragma once

#include <set>

// Path 
const std::string ASSET_PATH = "assets/img/";
const std::string FONT_PATH = "assets/fonts/";

// Window Parameters
constexpr unsigned short WINDOW_HEIGHT(1440);
constexpr unsigned short WINDOW_WIDTH(1920);

// Image Parameters
constexpr unsigned short MASK_OPACITY(60);

// Button Parameters
constexpr unsigned short BUTTON_HEIGHT(WINDOW_HEIGHT/8);
constexpr unsigned short BUTTON_WIDTH(BUTTON_HEIGHT*2);
constexpr char BUTTON_OUTLINE_THICKNESS(-5);
constexpr unsigned short SMALL_BUTTON_HEIGHT(WINDOW_HEIGHT/12);
constexpr unsigned short SMALL_BUTTON_WIDTH(SMALL_BUTTON_HEIGHT*2);

// Animation Parameters
constexpr unsigned short SLEEP_TIME(20);
constexpr unsigned short SLEEP_THRES(20);

// Inventory Parameters
constexpr char INVENTORY_SLOTS(10);
constexpr unsigned short INVENTORY_BLOCK_HEIGHT(100);
constexpr unsigned short INVENTORY_BLOCK_WIDTH(110);
constexpr unsigned short INVENTORY_OUTLINE_THICKNESS(7);
constexpr unsigned short INVENTORY_POS_X((WINDOW_WIDTH - INVENTORY_SLOTS*INVENTORY_BLOCK_WIDTH - (INVENTORY_SLOTS-1)*INVENTORY_OUTLINE_THICKNESS)/2);
constexpr unsigned short INVENTORY_POS_Y(WINDOW_HEIGHT - 1.5*INVENTORY_BLOCK_HEIGHT);

// Tool Parameters
constexpr unsigned short TOOL_HEIGHT(INVENTORY_BLOCK_HEIGHT);
constexpr unsigned short TOOL_WIDTH(INVENTORY_BLOCK_WIDTH);

// Tool ID
constexpr char SWORD(0);
constexpr char FAKESWORD(1);
constexpr char NAILS(2);
constexpr char WOOD(3);
constexpr char HAMMER(4);
constexpr char PENCIL(5);
constexpr char STICKS(6);
constexpr char LADDER(7);


// Tool List
const std::map<short,std::string> TOOL_LIST = {
    {SWORD, "sword"},
    {FAKESWORD, "fakesword"},
    {NAILS, "nails"},
    {WOOD, "wood"}, 
    {HAMMER, "hammer"},
    {PENCIL, "pencil"},
    {STICKS, "sticks"},
    {LADDER, "ladder"}
};

// Tool/Hint Trigger Properties
// Study Room
constexpr unsigned short BAG_XPOS(1650);
constexpr unsigned short BAG_YPOS(1050);
constexpr unsigned short BAG_TRIGGER_WIDTH(0.08*WINDOW_WIDTH);
constexpr unsigned short BAG_TRIGGER_HEIGHT(0.1*WINDOW_HEIGHT);

constexpr unsigned short LAPTOP_XPOS(1150);
constexpr unsigned short LAPTOP_YPOS(1000);
constexpr unsigned short LAPTOP_TRIGGER_WIDTH(0.13*WINDOW_WIDTH);
constexpr unsigned short LAPTOP_TRIGGER_HEIGHT(0.125*WINDOW_HEIGHT);

constexpr unsigned short STICKS_XPOS(1000);
constexpr unsigned short STICKS_YPOS(920);
constexpr unsigned short STICKS_TRIGGER_WIDTH(0.11*WINDOW_WIDTH);
constexpr unsigned short STICKS_TRIGGER_HEIGHT(0.07*WINDOW_HEIGHT);

constexpr unsigned short WHITEBOARD_XPOS(1100);
constexpr unsigned short WHITEBOARD_YPOS(450);
constexpr unsigned short WHITEBOARD_TRIGGER_WIDTH(0.37*WINDOW_WIDTH);
constexpr unsigned short WHITEBOARD_TRIGGER_HEIGHT(0.215*WINDOW_HEIGHT);

constexpr unsigned short UDOOR_XPOS(610);
constexpr unsigned short UDOOR_YPOS(470);
constexpr unsigned short UDOOR_TRIGGER_WIDTH(0.6*SMALL_BUTTON_WIDTH);
constexpr unsigned short UDOOR_TRIGGER_HEIGHT(4*SMALL_BUTTON_HEIGHT);

constexpr unsigned short UWINDOW_XPOS(320);
constexpr unsigned short UWINDOW_YPOS(420);
constexpr unsigned short UWINDOW_TRIGGER_WIDTH(0.7*SMALL_BUTTON_WIDTH);
constexpr unsigned short UWINDOW_TRIGGER_HEIGHT(3.5*SMALL_BUTTON_HEIGHT);

constexpr unsigned short UAC_XPOS(165);
constexpr unsigned short UAC_YPOS(735);
constexpr unsigned short UAC_TRIGGER_WIDTH(0.2*SMALL_BUTTON_WIDTH);
constexpr unsigned short UAC_TRIGGER_HEIGHT(0.5*SMALL_BUTTON_HEIGHT);

// Tea Room
constexpr unsigned short PENCIL_XPOS(1070);
constexpr unsigned short PENCIL_YPOS(865);
constexpr unsigned short PENCIL_TRIGGER_WIDTH(0.46*BUTTON_WIDTH);
constexpr unsigned short PENCIL_TRIGGER_HEIGHT(0.2*BUTTON_HEIGHT);

constexpr unsigned short BARISTA_XPOS(200);
constexpr unsigned short BARISTA_YPOS(860);
constexpr unsigned short BARISTA_TRIGGER_WIDTH(0.8*BUTTON_WIDTH);
constexpr unsigned short BARISTA_TRIGGER_HEIGHT(0.65*BUTTON_HEIGHT);

constexpr unsigned short PAPER_XPOS(35);
constexpr unsigned short PAPER_YPOS(535);
constexpr unsigned short PAPER_TRIGGER_WIDTH(0.35*BUTTON_WIDTH);
constexpr unsigned short PAPER_TRIGGER_HEIGHT(0.5*BUTTON_HEIGHT);

constexpr unsigned short REGISTER_XPOS(400);
constexpr unsigned short REGISTER_YPOS(550);
constexpr unsigned short REGISTER_TRIGGER_WIDTH(0.48*BUTTON_WIDTH);
constexpr unsigned short REGISTER_TRIGGER_HEIGHT(0.5*BUTTON_HEIGHT);

// EngSoc Lounge
constexpr unsigned short SWORD_XPOS(940);
constexpr unsigned short SWORD_YPOS(545);
constexpr unsigned short SWORD_TRIGGER_WIDTH(0.46*BUTTON_WIDTH);
constexpr unsigned short SWORD_TRIGGER_HEIGHT(0.2*BUTTON_HEIGHT);

constexpr unsigned short COMPUTER_XPOS(105);
constexpr unsigned short COMPUTER_YPOS(745);
constexpr unsigned short COMPUTER_TRIGGER_WIDTH(0.55*BUTTON_WIDTH);
constexpr unsigned short COMPUTER_TRIGGER_HEIGHT(0.6*BUTTON_HEIGHT);

constexpr unsigned short ENGSOC_DOOR_XPOS(1420);
constexpr unsigned short ENGSOC_DOOR_YPOS(700);
constexpr unsigned short ENGSOC_DOOR_TRIGGER_WIDTH(0.3*BUTTON_WIDTH);
constexpr unsigned short ENGSOC_DOOR_TRIGGER_HEIGHT(0.85*BUTTON_HEIGHT);

// Workshop
constexpr unsigned short NAILS_XPOS(310);
constexpr unsigned short NAILS_YPOS(825);
constexpr unsigned short NAILS_TRIGGER_WIDTH(100);
constexpr unsigned short NAILS_TRIGGER_HEIGHT(50);

constexpr unsigned short HAMMER_XPOS(1140);
constexpr unsigned short HAMMER_YPOS(960);
constexpr unsigned short HAMMER_TRIGGER_WIDTH(120);
constexpr unsigned short HAMMER_TRIGGER_HEIGHT(50);

constexpr unsigned short WOOD_XPOS(0);
constexpr unsigned short WOOD_YPOS(1060);
constexpr unsigned short WOOD_TRIGGER_WIDTH(100);
constexpr unsigned short WOOD_TRIGGER_HEIGHT(40);




// Dialog Box Parameters
constexpr unsigned short BACKSTORY_BOX_WIDTH(WINDOW_WIDTH);
constexpr unsigned short BACKSTORY_BOX_HEIGHT(WINDOW_HEIGHT/4);
constexpr unsigned short INTERACT_BOX_WIDTH(120);
constexpr unsigned short INTERACT_BOX_HEIGHT(60);

// Keypad Parameters
constexpr unsigned short KEYPAD_WIDTH(WINDOW_WIDTH/3);
constexpr unsigned short KEYPAD_HEIGHT(KEYPAD_WIDTH/0.92);
constexpr unsigned short KEYPAD_XPOS(0.4*WINDOW_HEIGHT);
constexpr unsigned short KEYPAD_YPOS(0.25*WINDOW_HEIGHT);

constexpr unsigned short CANCEL_XPOS(KEYPAD_XPOS+0.3*KEYPAD_WIDTH);
constexpr unsigned short CANCEL_YPOS(KEYPAD_YPOS+0.77*KEYPAD_HEIGHT);
constexpr unsigned short CANCEL_WIDTH(KEYPAD_WIDTH/2.5);
constexpr unsigned short CANCEL_HEIGHT(CANCEL_WIDTH/3);

constexpr unsigned short DISPLAY_XPOS(KEYPAD_XPOS+0.15*KEYPAD_WIDTH);
constexpr unsigned short DISPLAY_YPOS(KEYPAD_YPOS+0.15*KEYPAD_HEIGHT);
constexpr unsigned short DISPLAY_WIDTH(0.7*KEYPAD_WIDTH);
constexpr unsigned short DISPLAY_HEIGHT(0.16*KEYPAD_HEIGHT);

constexpr unsigned short MESSAGE_XPOS(DISPLAY_XPOS);
constexpr unsigned short MESSAGE_YPOS(DISPLAY_YPOS+DISPLAY_HEIGHT+0.05*KEYPAD_HEIGHT);

// Workbench Parameters
constexpr unsigned short WORKBENCH_WIDTH(WINDOW_WIDTH);
constexpr unsigned short WORKBENCH_HEIGHT(WINDOW_WIDTH/1.8);
constexpr unsigned short WORKBENCH_XPOS(0);
constexpr unsigned short WORKBENCH_YPOS(WINDOW_HEIGHT/10);

constexpr unsigned short WORKBENCH_CLOSE_BUTTON_WIDTH(60);
constexpr unsigned short WORKBENCH_CLOSE_BUTTON_HEIGHT(60);
constexpr unsigned short WORKBENCH_CLOSE_BUTTON_XPOS(WINDOW_WIDTH-WORKBENCH_CLOSE_BUTTON_WIDTH);
constexpr unsigned short WORKBENCH_CLOSE_BUTTON_YPOS(WORKBENCH_YPOS);

constexpr unsigned short WORKBENCH_ASSEMBLE_BUTTON_WIDTH(200);
constexpr unsigned short WORKBENCH_ASSEMBLE_BUTTON_HEIGHT(100);
constexpr unsigned short WORKBENCH_ASSEMBLE_BUTTON_XPOS(0.43*WINDOW_WIDTH);
constexpr unsigned short WORKBENCH_ASSEMBLE_BUTTON_YPOS(WORKBENCH_YPOS+0.9*WORKBENCH_HEIGHT);

constexpr unsigned char NUMBER_OF_ASSEMBLING_PARTS(3);  // Temporary Value for testing purpose.
const std::set<int> WORKBENCH_TOOLS = {NAILS, WOOD, HAMMER};       // Temporary List for testing purpose. 


