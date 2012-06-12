
#ifndef TOOLS_HH_
# define TOOLS_HH_

# include <string>


/// @brief Convert the given string into a decimal representation
/// Check if it's an hexa, octal, binary or decimal number and call
/// the good function.
//
/// @param num is the number to convert
///
/// @return the result of the conversion
int convert (std::string& num);


/// @brief Convert num (which is a decimal number) into an int
///
/// @param num is the string to convert
///
/// @return the result of the conversion
int string_to_int (std::string& num);


/// @brief Convert a num (which is an hexa number) into a decimal int
///
/// @param num is the string to convert
///
/// @return the result of the conversion
int hexa_to_int (std::string& num);


/// @brief Convert a num (which is an octal number) into a decimal int
///
/// @param num is the string to convert
///
/// @return the result of the conversion
int oct_to_int (std::string& num);


/// @brief Convert a num (which is a binary number) into a decimal int
///
/// @param num is the string to convert
///
/// @return the result of the conversion
int bin_to_int (std::string& num);

#endif /* !TOOLS_HH_ */
