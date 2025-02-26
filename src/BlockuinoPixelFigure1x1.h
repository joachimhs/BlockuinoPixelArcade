#ifndef BLOCKUINO_PIXEL_FIGURE_1X1_H
#define BLOCKUINO_PIXEL_FIGURE_1X1_H

#include "BlockuinoPixelArcade.h"

/**
 * Concrete implementation of BlockuinoPixelFigure for a 1x1 figure.
 */
class BlockuinoPixelFigure1x1 : public BlockuinoPixelFigure {
private:
    uint32_t color; // Color of the single pixel

public:
    /**
     * Constructor
     * @param colorStr     Hexadecimal color string (e.g., "#ff0000")
     * @param startIndex   The initial position index on the LED panel
     * @param panelSize    The size of the LED panel (panelSize x panelSize)
     */
    BlockuinoPixelFigure1x1(const String colorsStr[1], int startIndex, int panelSize);

    /**
     * Draw the 1x1 figure onto the NeoPixel strip.
     */
    void draw() override;
	
	/**
     * Check if a specific pixel is occupied.
     * @param pixelIndex Absolute index of the pixel on the panel.
     * @return true if the pixel is occupied (non-black), false otherwise.
     */
    bool isPixelOccupied(int pixelIndex) const override;
};

#endif // BLOCKUINO_PIXEL_FIGURE_1X1_H
