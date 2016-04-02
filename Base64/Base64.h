//  //
// ####   ###     ##                -= Base64 library =-                 //
// #   # #       # # Base64.h - Base64 encoder/decoder                   //
// ####  ####   #  #                                                     //
// #   # #   # ##### Encodes and decodes base64 strings                  //
// #   # #   #     # Ideas taken from work done by Bob Withers           //
// ####   ###      # R1                      2002-05-07 by Markus Ewald  //
//  //

//此函数从MediaInfoLib中剥离出来，并注释了inline保留字
#ifndef B64_BASE64_H
#define B64_BASE64_H

#include <string>

namespace Base64 {

	/// Encode string to base64
	/*inline*/ std::string encode(const std::string &sString);
	/// Encode base64 into string
	/*inline*/ std::string decode(const std::string &sString);

}; // namespace Base64


#endif // B64_BASE64_H