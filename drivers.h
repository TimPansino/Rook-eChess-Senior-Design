// Numeric Definitions
#define RED     4
#define GREEN   2
#define BLUE    1
#define MAGENTA RED|BLUE
#define CYAN    GREEN|BLUE
#define YELLOW  RED|GREEN
#define WHITE   RED|GREEN|BLUE
#define BLACK   0
#define OFF     BLACK

// Aliases
#define PURPLE  MAGENTA
#define GOLD    YELLOW
#define ON      WHITE

// Shifting Amounts
#define R_SHIFT RED/2
#define G_SHIFT GREEN/2
#define B_SHIFT BLUE/2

// Color Choices
#define C_ERROR     RED
#define C_POSSIBLE  BLUE
#define C_CAPTURE   GREEN
#define C_CHECK     YELLOW
#define C_SPECIAL   PURPLE

// Type Definitions
typedef char Color;
typedef Color C[8][8];

// Function Declarations
void blankColors(C board);
void updateLeds(C curBoard, C prevBoard);
