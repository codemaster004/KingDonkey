//
// Created by Filip Dabkowski on 16/12/2023.
//

#ifndef KINGDONKEY_BITDICT_H
#define KINGDONKEY_BITDICT_H

#include "cstdint"


/**
 * @class BitDict - Efficiently store and manipulate a collection of bits.
 *
 * @brief This class provides functionality to easily store and manipulate true/false values accessible by index.
 *
 * @details This class provides functionalities to set, get, and remove bits at specific indices.
 * It uses an array of uint8_t to represent the bits, allowing for compact storage.
 *
 * @example
 * @code
 * BitDict bitDict(16);
 * bitDict.set(3);
 * bool bit = bitDict.get(3);  // bit is now true
 * bitDict.remove(3);
 * bit = bitDict.get(3);  // bit is now false
 *
 */
class BitDict {
private:
	uint8_t *dict; ///< Pointer to the array of uint8_t that stores the bits.
	uint8_t size; ///< The size of the bit array.

	/**
     * @brief Generates a bit mask with a 1 at the specified bit index.
     * @param index The bit position for which the mask is generated.
     * @return A uint8_t mask.
     */
	static uint8_t mask(uint8_t index);

	/**
     * @brief Checks if the given index is within the bounds of the bit array.
     * @param index The index to check.
     * @return True if index is within the size of the bit array, false otherwise.
     */
	[[nodiscard]] bool checkSize(int index) const;

public:
	/**
     * @brief Constructor: Initializes the BitDict with a specific number of bits.
     * @param maxBits The number of bits to initialize. Defaults to 8 bits. Use only numbers dividable by 8.
     */
	explicit BitDict(int maxBits = 8) : size((uint8_t)(maxBits)) {
		dict = new uint8_t[size / 8];
		reset();
	}


	/// Destructor: Cleans up the dynamically allocated memory.
	~BitDict() {
		delete[] dict;
	};

	/**
     * @brief Sets the bit at the specified index to 1.
     * @param index The index of the bit to set.
     */
	void set(int index);

	/**
     * @brief Retrieves the value of the bit at the specified index.
     * @param index The index of the bit to get.
     * @return True if the bit is set, false otherwise.
     */
	bool get(int index);

	/**
     * @brief Sets the bit at the specified index to 0.
     * @param index The index of the bit to remove.
     */
	void remove(int index);

	/**
	 * @brief Resets all bits in the BitDict to 0 (false).
	 *
	 * @details This function sets every bit in the BitDict's internal array to 0 (false),
	 * actively resetting the array.
	 */
	void reset();
};


#endif //KINGDONKEY_BITDICT_H
