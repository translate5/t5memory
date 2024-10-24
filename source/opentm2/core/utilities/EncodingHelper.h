#ifndef _ENCODING_HELPER_H_
#define _ENCODING_HELPER_H_

#include <string>
#include <vector>


class EncodingHelper{
    public:
    /*! \brief convert a UTF8 std::string to a UTF16 std::wstring
    \param strUTF8String string in UTF8 encoding
    \returns string converted to UTF16
    */
    std::wstring static convertToUTF16(std::string&& strUTF8String);
    std::u16string static toUtf16(std::wstring&& wstr);
    std::wstring static toWChar(std::u16string u16str);
    std::string static toChar(std::u16string u16str);

    /*! \brief convert a UTF8 std::string to a UTF16 std::wstring
    \param strUTF8String string in UTF8 encoding
    \returns string converted to UTF16
    */
    std::string static convertToUTF8( const std::wstring& strUTF16String );

    /*! \brief convert a UTF8 std::string to a UTF16 std::wstring
    \param strUTF8String string in UTF8 encoding
    \returns string converted to UTF16
    */
    std::string static convertToUTF8( const std::u16string& strUTF16String );
    std::string static convertToUTF8( const wchar_t* UTF16String);

    /*! \brief convert a UTF8 std::string to a ASCII std::string (on spot conversion)
    \param strText on input string in UTF8 encoding, on output string in ASCII encoding
    */
    void static convertUTF8ToASCII( std::string& strText );

    /*! \brief convert a ASCII std::string to UTF8 std::string (on spot conversion)
    \param strText on input string in ASCII encoding, on output string in UTF8 encoding
    */
    void static convertASCIIToUTF8( std::string& strText );

    std::u16string static toLower(const std::u16string& strText);

    void static Base64Encode (const unsigned char* input, int inSize, std::string& output);
    void static Base64Decode (const std::string& input, unsigned char *& output, int& output_size);

    static std::wstring EscapeXML( std::wstring input );
    static std::vector<std::wstring> ReplaceOriginalTagsWithPlaceholders(std::wstring &&w_src, std::wstring &&w_trg = L"", std::wstring &&w_req = L"");

};

#endif
