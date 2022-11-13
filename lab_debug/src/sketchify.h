/**
 * @file sketchify.h
 * Declaration of the sketchify function.
 */

#pragma once

#include <string>

/**
 * Reads in an image, runs a simple "sketchify" algorithm on it to highlight
 * edges in the image, and then writes the resulting image back out to a
 * specified file.

 * @param inputFile the name of the PNG file to sketchify
 * @param outputFile the name of the file where the output will be written
 */
void sketchify(std::string inputFile, std::string outputFile);
