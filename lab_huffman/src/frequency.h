/**
 * @file frequency.h
 * Definition of a character frequency class.
 */

#pragma once

/**
 * Frequency: a plain-old-data type representing a character and its
 * frequency. Used by the HuffmanTree as the data element of the TreeNodes.
 * If a node is an internal node, the character is the null character ('\0').
 */
class Frequency
{
  public:
    /**
     * Constructs a new Frequency object from a given character and its
     * associated frequency in a file.
     *
     * @param character The character this Frequency represents.
     * @param frequency The number of times this character appears in
     *	the file.
     */
    Frequency(char character, int frequency);

    /**
     * Constructs a new Frequency object from a given frequency count.
     * Frequencies created this way have the null character ('\0') as
     * their character data (these kinds of Frequency objects are used
     * as the data of internal nodes in the HuffmanTree).
     *
     * @param frequency The number to be stored.
     */
    Frequency(int frequency);

    /**
     * Getter for the character for this Frequency object.
     *
     * @return The character for this Frequency.
     */
    char getCharacter() const;

    /**
     * Getter for the frequency for this Frequency object.
     *
     * @return The frequency member of this object.
     */
    int getFrequency() const;

    /**
     * Comparison operator for Frequency objects. Allows for sorting
     * with std::sort.
     *
     * @param other The Frequency object to compare against.
     * @return Whether the current frequency is less than the given
     *	frequency (other).
     */
    bool operator<(const Frequency& other) const;

    /**
     * Comparison operator for Frequency objects. Allows for
     * determining whether the Frequency is the same as another.
     *
     * @param other The Frequency object to compare against.
     * @return Whether the current Frequency is the same as
     *  the given Frequency (other).
     */
    bool operator==(const Frequency& other) const;

  private:
    char character_;
    int frequency_;
};
