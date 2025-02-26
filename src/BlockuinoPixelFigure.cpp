#include "BlockuinoPixelArcade.h"

// Define BLACK color for convenience
static const uint32_t BLACK = 0;

/**
 * Move the figure one step to the left, respecting panel boundaries.
 */
void BlockuinoPixelFigure::moveLeft() {
    int row = position / panelSize;
    int col = position % panelSize;

    // Ensure the figure doesn't move beyond the left edge
    if (col > 0) {
        position--;
    }
}

/**
 * Move the figure one step to the right, respecting panel boundaries.
 */
void BlockuinoPixelFigure::moveRight() {
    int row = position / panelSize;
    int col = position % panelSize;

    int maxCol = panelSize - figureSize;
    if (col < maxCol) {
        position++;
    }
}

/**
 * Move the figure one step up, respecting panel boundaries.
 */
void BlockuinoPixelFigure::moveUp() {
    int row = position / panelSize;

    // Ensure the figure doesn't move beyond the top edge
    if (row > 0) {
        position -= panelSize;
    }
}

/**
 * Move the figure one step down, respecting panel boundaries.
 */
void BlockuinoPixelFigure::moveDown() {
    int row = position / panelSize;
    int maxRow = panelSize - figureSize;

    // Ensure the figure doesn't move beyond the bottom edge
    if (row < maxRow) {
        position += panelSize;
    }
}

/**
 * Move the figure to a specific position index, clamping if necessary.
 */
void BlockuinoPixelFigure::moveTo(int newPosition) {
    int totalPixels = panelSize * panelSize;
    
    // Clamp the newPosition within valid range
    if (newPosition < 0) newPosition = 0;
    if (newPosition >= totalPixels) newPosition = totalPixels - 1;

    // Convert to row and column
    int newRow = newPosition / panelSize;
    int newCol = newPosition % panelSize;

    // Clamp to ensure the entire NxN figure fits within the panel
    int maxRow = panelSize - figureSize;
    int maxCol = panelSize - figureSize;
    if (newRow > maxRow) newRow = maxRow;
    if (newCol > maxCol) newCol = maxCol;

    position = newRow * panelSize + newCol;
}

/**
 * Check if this figure overlaps with another figure based on non-black pixels.
 */
bool BlockuinoPixelFigure::doesHit(const BlockuinoPixelFigure &other) {
    // Convert positions to row and column
    int rowA = position / panelSize;
    int colA = position % panelSize;
    int rowB = other.position / panelSize;
    int colB = other.position % panelSize;

    // Dimensions
    int sizeA = figureSize;
    int sizeB = other.figureSize;

    // Calculate bounding boxes
    int leftA = colA;
    int rightA = colA + sizeA - 1;
    int topA = rowA;
    int bottomA = rowA + sizeA - 1;

    int leftB = colB;
    int rightB = colB + sizeB - 1;
    int topB = rowB;
    int bottomB = rowB + sizeB - 1;

    // Find overlapping rectangle
    int overlapLeft = (leftA > leftB) ? leftA : leftB;
    int overlapRight = (rightA < rightB) ? rightA : rightB;
    int overlapTop = (topA > topB) ? topA : topB;
    int overlapBottom = (bottomA < bottomB) ? bottomA : bottomB;

    // Check if there is any overlapping area
    if (overlapLeft > overlapRight || overlapTop > overlapBottom) {
        return false; // No overlapping
    }

    // Iterate through the overlapping pixels
    for (int row = overlapTop; row <= overlapBottom; row++) {
        for (int col = overlapLeft; col <= overlapRight; col++) {
            int pixelIndex = row * panelSize + col;
            if (this->isPixelOccupied(pixelIndex) && other.isPixelOccupied(pixelIndex)) {
                return true; // Collision detected
            }
        }
    }

    return false; // No collision detected
}

void BlockuinoPixelFigure::setDirection(char newDirection) {
    direction = newDirection;
}

char BlockuinoPixelFigure::getDirection() {
    return direction;
}

void BlockuinoPixelFigure::rotateClockwise() {
    switch (direction) {
        case 'N': direction = 'E'; break;
        case 'E': direction = 'S'; break;
        case 'S': direction = 'W'; break;
        case 'W': direction = 'N'; break;
    }
}

void BlockuinoPixelFigure::rotateCounterClockwise() {
    switch (direction) {
        case 'N': direction = 'W'; break;
        case 'W': direction = 'S'; break;
        case 'S': direction = 'E'; break;
        case 'E': direction = 'N'; break;
    }
}

// Initialize static instance pointer
PixelUtility& PixelUtility::getInstance() {
    static PixelUtility instance;
    return instance;
}

// Private Constructor
PixelUtility::PixelUtility()
    : strip(nullptr), // Initialize pointer to null
      strip_alternating_direction(false),
      strip_swap_horizontal_and_vertical_direction(false)
{}

// Initialize the PixelUtility with an external strip
void PixelUtility::begin(Adafruit_NeoPixel* externalStrip) {
    if (externalStrip != nullptr) {
        strip = externalStrip;
    } else {
        Serial.println("Error: External strip is null.");
    }
}

// Accessor for strip_alternating_direction
bool PixelUtility::isAlternatingDirection() const {
    return strip_alternating_direction;
}

// Mutator for strip_alternating_direction
void PixelUtility::setAlternatingDirection(bool state) {
    strip_alternating_direction = state;
}

// Accessor for strip_swap_horizontal_and_vertical_direction
bool PixelUtility::isSwapDirections() const {
    return strip_swap_horizontal_and_vertical_direction;
}

// Mutator for strip_swap_horizontal_and_vertical_direction
void PixelUtility::setSwapDirections(bool state) {
    strip_swap_horizontal_and_vertical_direction = state;
}

// Utility Function: Swap Directions
int PixelUtility::pixel_swap_directions(int pixel, int pixelWidth) {
    if (pixel < 0 || pixel >= pixelWidth * pixelWidth) {
        // Handle invalid pixel indices
        Serial.print("Error: Pixel index ");
        Serial.print(pixel);
        Serial.print(" out of bounds for grid size ");
        Serial.print(pixelWidth);
        Serial.print("x");
        Serial.println(pixelWidth);
        return -1; // Indicate an error
    }

    int row = pixel % pixelWidth; // Original row (vertical position)
    int col = pixel / pixelWidth; // Original column (horizontal position)

    int newPixel = row * pixelWidth + col;

    return newPixel;
}

// Utility Function: Translate Pixel Index
int PixelUtility::pixel_matrixPixel(int pixel) {
    if (strip == nullptr) {
        Serial.println("Error: Strip not initialized.");
        return -1;
    }
    uint16_t numPixels = strip->numPixels();
    int matrixWidth = sqrt(numPixels);
    int riktigPixel = pixel;

    if (strip_swap_horizontal_and_vertical_direction) {
        riktigPixel = pixel_swap_directions(pixel, matrixWidth);
    }

    if (strip_alternating_direction) {
        int kolonne = riktigPixel / matrixWidth;
        int rad = riktigPixel % matrixWidth;

        if (kolonne % 2 != 0) { // Changed from (kolonne % 2 != (0)) to (kolonne % 2 != 0)
            riktigPixel = kolonne * matrixWidth + (matrixWidth - 1) - rad;
        }
    }

    return riktigPixel;
}

// Utility Function: Clear All Pixels
void PixelUtility::pixel_clear() {
    if (strip == nullptr) {
        Serial.println("Error: Strip not initialized.");
        return;
    }

    strip->clear();
}

uint32_t PixelUtility::pixel_random_color() {
    int pixelr = random(0, 50);
    int pixelg = random(0, 50);
    int pixelb = random(0, 50);

    return strip->Color(pixelr, pixelg, pixelb);
}

int PixelUtility::pixel_moveLeft(int position) {
    int matrixWidth = sqrt(strip->numPixels());
    if ((position % matrixWidth)> 0) {
        position--;
    }
    return position;
}

int PixelUtility::pixel_moveRight(int position) {
    int matrixWidth = sqrt(strip->numPixels());
    if (((position + 1) % matrixWidth)> 0) {
        position++;
    }
    return position;
}

int PixelUtility::pixel_moveUp(int position) {
    int matrixWidth = sqrt(strip->numPixels());
    if ((position - matrixWidth) >= 0) {
        position -= matrixWidth;
    }
    return position;
}

int PixelUtility::pixel_moveDown(int position) {
    int matrixWidth = sqrt(strip->numPixels());
    if ((position + matrixWidth) < strip->numPixels()) {
        position += matrixWidth;
    }
    return position;
}

// Accessor for the NeoPixel Strip
Adafruit_NeoPixel& PixelUtility::getStrip() {
    if (strip == nullptr) {
        Serial.println("Error: Strip not initialized.");
        // Return a reference to a temporary strip to prevent undefined behavior
        // Alternatively, handle this case more gracefully
    }
    return *strip;
}