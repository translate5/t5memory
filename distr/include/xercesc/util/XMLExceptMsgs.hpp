// This file is generated, don't edit it!!

#if !defined(XERCESC_INCLUDE_GUARD_ERRHEADER_XMLExcepts)
#define XERCESC_INCLUDE_GUARD_ERRHEADER_XMLExcepts

#include <xercesc/util/XercesDefs.hpp>
#include <xercesc/dom/DOMError.hpp>

XERCES_CPP_NAMESPACE_BEGIN

class XMLExcepts
{
public :
    enum Codes
    {
        NoError                            = 0
      , W_LowBounds                        = 1
      , Scan_CouldNotOpenSource_Warning    = 2
      , W_HighBounds                       = 3
      , F_LowBounds                        = 4
      , Array_BadIndex                     = 5
      , Array_BadNewSize                   = 6
      , AttrList_BadIndex                  = 7
      , AttDef_BadAttType                  = 8
      , AttDef_BadDefAttType               = 9
      , Bitset_BadIndex                    = 10
      , Bitset_NotEqualSize                = 11
      , BufMgr_NoMoreBuffers               = 12
      , BufMgr_BufferNotInPool             = 13
      , CPtr_PointerIsZero                 = 14
      , CM_BinOpHadUnaryType               = 15
      , CM_MustBeMixedOrChildren           = 16
      , CM_NoPCDATAHere                    = 17
      , CM_UnaryOpHadBinType               = 18
      , CM_UnknownCMType                   = 19
      , CM_UnknownCMSpecType               = 20
      , CM_NoParentCSN                     = 21
      , CM_NotValidSpecTypeForNode         = 22
      , DTD_UnknownCreateReason            = 23
      , ElemStack_EmptyStack               = 24
      , ElemStack_StackUnderflow           = 25
      , ElemStack_NoParentPushed           = 26
      , Enum_NoMoreElements                = 27
      , File_CouldNotOpenFile              = 28
      , File_CouldNotGetCurPos             = 29
      , File_CouldNotCloseFile             = 30
      , File_CouldNotSeekToEnd             = 31
      , File_CouldNotSeekToPos             = 32
      , File_CouldNotDupHandle             = 33
      , File_CouldNotReadFromFile          = 34
      , File_CouldNotWriteToFile           = 35
      , File_CouldNotResetFile             = 36
      , File_CouldNotGetSize               = 37
      , File_CouldNotGetBasePathName       = 38
      , Gen_ParseInProgress                = 39
      , Gen_NoDTDValidator                 = 40
      , Gen_CouldNotOpenDTD                = 41
      , Gen_CouldNotOpenExtEntity          = 42
      , Gen_UnexpectedEOF                  = 43
      , HshTbl_ZeroModulus                 = 44
      , HshTbl_BadHashFromKey              = 45
      , HshTbl_NoSuchKeyExists             = 46
      , Mutex_CouldNotDestroy              = 47
      , NetAcc_InternalError               = 48
      , NetAcc_LengthError                 = 49
      , NetAcc_InitFailed                  = 50
      , NetAcc_TargetResolution            = 51
      , NetAcc_CreateSocket                = 52
      , NetAcc_ConnSocket                  = 53
      , NetAcc_WriteSocket                 = 54
      , NetAcc_ReadSocket                  = 55
      , NetAcc_UnsupportedMethod           = 56
      , Pool_ElemAlreadyExists             = 57
      , Pool_InvalidId                     = 58
      , Pool_ZeroModulus                   = 59
      , RdrMgr_ReaderIdNotFound            = 60
      , Reader_BadAutoEncoding             = 61
      , Reader_CouldNotDecodeFirstLine     = 62
      , Reader_NelLsepinDecl               = 63
      , Reader_SrcOfsNotSupported          = 64
      , Reader_EncodingStrRequired         = 65
      , Scan_CouldNotOpenSource            = 66
      , Scan_UnbalancedStartEnd            = 67
      , Scan_BadPScanToken                 = 68
      , Stack_BadIndex                     = 69
      , Stack_EmptyStack                   = 70
      , Str_ZeroSizedTargetBuf             = 71
      , Str_UnknownRadix                   = 72
      , Str_TargetBufTooSmall              = 73
      , Str_StartIndexPastEnd              = 74
      , Str_ConvertOverflow                = 75
      , StrPool_IllegalId                  = 76
      , Trans_Unrepresentable              = 77
      , Trans_BadSrcSeq                    = 78
      , Trans_BadSrcCP                     = 79
      , Trans_BadTrailingSurrogate         = 80
      , Trans_CantCreateCvtrFor            = 81
      , URL_MalformedURL                   = 82
      , URL_UnsupportedProto               = 83
      , URL_UnsupportedProto1              = 84
      , URL_NoProtocolPresent              = 85
      , URL_ExpectingTwoSlashes            = 86
      , URL_RelativeBaseURL                = 87
      , URL_BadPortField                   = 88
      , UTF8_FormatError                   = 89
      , UTF8_Invalid_3BytesSeq             = 90
      , UTF8_Irregular_3BytesSeq           = 91
      , UTF8_Invalid_4BytesSeq             = 92
      , UTF8_Exceeds_BytesLimit            = 93
      , Vector_BadIndex                    = 94
      , Val_InvalidElemId                  = 95
      , Val_CantHaveIntSS                  = 96
      , XMLRec_UnknownEncoding             = 97
      , Parser_Parse1                      = 98
      , Parser_Parse2                      = 99
      , Parser_Next1                       = 100
      , Parser_Next2                       = 101
      , Parser_Next3                       = 102
      , Parser_Next4                       = 103
      , Parser_Factor1                     = 104
      , Parser_Factor2                     = 105
      , Parser_Factor3                     = 106
      , Parser_Factor4                     = 107
      , Parser_Factor5                     = 108
      , Parser_Factor6                     = 109
      , Parser_Atom1                       = 110
      , Parser_Atom2                       = 111
      , Parser_Atom3                       = 112
      , Parser_Atom4                       = 113
      , Parser_Atom5                       = 114
      , Parser_CC1                         = 115
      , Parser_CC2                         = 116
      , Parser_CC3                         = 117
      , Parser_CC5                         = 118
      , Parser_CC6                         = 119
      , Parser_Ope1                        = 120
      , Parser_Ope2                        = 121
      , Parser_Ope3                        = 122
      , Parser_Descape1                    = 123
      , Parser_Descape3                    = 124
      , Parser_Descape4                    = 125
      , Parser_Descape5                    = 126
      , Parser_Process2                    = 127
      , Parser_Quantifier1                 = 128
      , Parser_Quantifier2                 = 129
      , Parser_Quantifier3                 = 130
      , Parser_Quantifier4                 = 131
      , Parser_Quantifier5                 = 132
      , Gen_NoSchemaValidator              = 133
      , SubGrpComparator_NGR               = 134
      , FACET_Invalid_Len                  = 135
      , FACET_Invalid_maxLen               = 136
      , FACET_Invalid_minLen               = 137
      , FACET_NonNeg_Len                   = 138
      , FACET_NonNeg_maxLen                = 139
      , FACET_NonNeg_minLen                = 140
      , FACET_Len_maxLen                   = 141
      , FACET_Len_minLen                   = 142
      , FACET_maxLen_minLen                = 143
      , FACET_Invalid_Tag                  = 144
      , FACET_Len_baseLen                  = 145
      , FACET_minLen_baseminLen            = 146
      , FACET_minLen_basemaxLen            = 147
      , FACET_maxLen_basemaxLen            = 148
      , FACET_maxLen_baseminLen            = 149
      , FACET_Len_baseMinLen               = 150
      , FACET_Len_baseMaxLen               = 151
      , FACET_minLen_baseLen               = 152
      , FACET_maxLen_baseLen               = 153
      , FACET_enum_base                    = 154
      , FACET_Invalid_WS                   = 155
      , FACET_WS_collapse                  = 156
      , FACET_WS_replace                   = 157
      , FACET_Invalid_MaxIncl              = 158
      , FACET_Invalid_MaxExcl              = 159
      , FACET_Invalid_MinIncl              = 160
      , FACET_Invalid_MinExcl              = 161
      , FACET_Invalid_TotalDigit           = 162
      , FACET_Invalid_FractDigit           = 163
      , FACET_PosInt_TotalDigit            = 164
      , FACET_NonNeg_FractDigit            = 165
      , FACET_max_Incl_Excl                = 166
      , FACET_min_Incl_Excl                = 167
      , FACET_maxExcl_minExcl              = 168
      , FACET_maxExcl_minIncl              = 169
      , FACET_maxIncl_minExcl              = 170
      , FACET_maxIncl_minIncl              = 171
      , FACET_TotDigit_FractDigit          = 172
      , FACET_maxIncl_base_maxExcl         = 173
      , FACET_maxIncl_base_maxIncl         = 174
      , FACET_maxIncl_base_minIncl         = 175
      , FACET_maxIncl_base_minExcl         = 176
      , FACET_maxExcl_base_maxExcl         = 177
      , FACET_maxExcl_base_maxIncl         = 178
      , FACET_maxExcl_base_minIncl         = 179
      , FACET_maxExcl_base_minExcl         = 180
      , FACET_minExcl_base_maxExcl         = 181
      , FACET_minExcl_base_maxIncl         = 182
      , FACET_minExcl_base_minIncl         = 183
      , FACET_minExcl_base_minExcl         = 184
      , FACET_minIncl_base_maxExcl         = 185
      , FACET_minIncl_base_maxIncl         = 186
      , FACET_minIncl_base_minIncl         = 187
      , FACET_minIncl_base_minExcl         = 188
      , FACET_maxIncl_notFromBase          = 189
      , FACET_maxExcl_notFromBase          = 190
      , FACET_minIncl_notFromBase          = 191
      , FACET_minExcl_notFromBase          = 192
      , FACET_totalDigit_base_totalDigit   = 193
      , FACET_fractDigit_base_totalDigit   = 194
      , FACET_fractDigit_base_fractDigit   = 195
      , FACET_maxIncl_base_fixed           = 196
      , FACET_maxExcl_base_fixed           = 197
      , FACET_minIncl_base_fixed           = 198
      , FACET_minExcl_base_fixed           = 199
      , FACET_totalDigit_base_fixed        = 200
      , FACET_fractDigit_base_fixed        = 201
      , FACET_maxLen_base_fixed            = 202
      , FACET_minLen_base_fixed            = 203
      , FACET_whitespace_base_fixed        = 204
      , FACET_internalError_fixed          = 205
      , FACET_List_Null_baseValidator      = 206
      , FACET_Union_Null_memberTypeValidators   = 207
      , FACET_Union_Null_baseValidator     = 208
      , FACET_Union_invalid_baseValidatorType   = 209
      , VALUE_NotMatch_Pattern             = 210
      , VALUE_Not_Base64                   = 211
      , VALUE_Not_HexBin                   = 212
      , VALUE_GT_maxLen                    = 213
      , VALUE_LT_minLen                    = 214
      , VALUE_NE_Len                       = 215
      , VALUE_NotIn_Enumeration            = 216
      , VALUE_exceed_totalDigit            = 217
      , VALUE_exceed_fractDigit            = 218
      , VALUE_exceed_maxIncl               = 219
      , VALUE_exceed_maxExcl               = 220
      , VALUE_exceed_minIncl               = 221
      , VALUE_exceed_minExcl               = 222
      , VALUE_WS_replaced                  = 223
      , VALUE_WS_collapsed                 = 224
      , VALUE_Invalid_NCName               = 225
      , VALUE_Invalid_Name                 = 226
      , VALUE_ID_Not_Unique                = 227
      , VALUE_ENTITY_Invalid               = 228
      , VALUE_QName_Invalid                = 229
      , VALUE_NOTATION_Invalid             = 230
      , VALUE_no_match_memberType          = 231
      , VALUE_URI_Malformed                = 232
      , XMLNUM_emptyString                 = 233
      , XMLNUM_WSString                    = 234
      , XMLNUM_2ManyDecPoint               = 235
      , XMLNUM_Inv_chars                   = 236
      , XMLNUM_null_ptr                    = 237
      , XMLNUM_URI_Component_Empty         = 238
      , XMLNUM_URI_Component_for_GenURI_Only   = 239
      , XMLNUM_URI_Component_Invalid_EscapeSequence   = 240
      , XMLNUM_URI_Component_Invalid_Char   = 241
      , XMLNUM_URI_Component_Set_Null      = 242
      , XMLNUM_URI_Component_Not_Conformant   = 243
      , XMLNUM_URI_No_Scheme               = 244
      , XMLNUM_URI_NullHost                = 245
      , XMLNUM_URI_NullPath                = 246
      , XMLNUM_URI_PortNo_Invalid          = 247
      , XMLNUM_DBL_FLT_InvalidType         = 248
      , Regex_Result_Not_Set               = 249
      , Regex_CompactRangesError           = 250
      , Regex_MergeRangesTypeMismatch      = 251
      , Regex_SubtractRangesError          = 252
      , Regex_IntersectRangesError         = 253
      , Regex_ComplementRangesInvalidArg   = 254
      , Regex_InvalidCategoryName          = 255
      , Regex_KeywordNotFound              = 256
      , Regex_BadRefNo                     = 257
      , Regex_UnknownOption                = 258
      , Regex_UnknownTokenType             = 259
      , Regex_RangeTokenGetError           = 260
      , Regex_NotSupported                 = 261
      , Regex_InvalidChildIndex            = 262
      , Regex_RepPatMatchesZeroString      = 263
      , Regex_InvalidRepPattern            = 264
      , NEL_RepeatedCalls                  = 265
      , Out_Of_Memory                      = 266
      , DV_InvalidOperation                = 267
      , XPath_NoAttrSelector               = 268
      , XPath_NoUnionAtStart               = 269
      , XPath_NoMultipleUnion              = 270
      , XPath_MissingAttr                  = 271
      , XPath_ExpectedToken1               = 272
      , XPath_PrefixNoURI                  = 273
      , XPath_NoDoubleColon                = 274
      , XPath_ExpectedStep1                = 275
      , XPath_ExpectedStep2                = 276
      , XPath_ExpectedStep3                = 277
      , XPath_NoForwardSlash               = 278
      , XPath_NoDoubleForwardSlash         = 279
      , XPath_NoForwardSlashAtStart        = 280
      , XPath_NoSelectionOfRoot            = 281
      , XPath_EmptyExpr                    = 282
      , XPath_NoUnionAtEnd                 = 283
      , XPath_InvalidChar                  = 284
      , XPath_TokenNotSupported            = 285
      , XPath_FindSolution                 = 286
      , DateTime_dt_invalid                = 287
      , DateTime_dt_missingT               = 288
      , DateTime_gDay_invalid              = 289
      , DateTime_gMth_invalid              = 290
      , DateTime_gMthDay_invalid           = 291
      , DateTime_dur_invalid               = 292
      , DateTime_dur_Start_dashP           = 293
      , DateTime_dur_noP                   = 294
      , DateTime_dur_DashNotFirst          = 295
      , DateTime_dur_inv_b4T               = 296
      , DateTime_dur_NoTimeAfterT          = 297
      , DateTime_dur_NoElementAtAll        = 298
      , DateTime_dur_inv_seconds           = 299
      , DateTime_date_incomplete           = 300
      , DateTime_date_invalid              = 301
      , DateTime_time_incomplete           = 302
      , DateTime_time_invalid              = 303
      , DateTime_ms_noDigit                = 304
      , DateTime_ym_incomplete             = 305
      , DateTime_ym_invalid                = 306
      , DateTime_year_invalid              = 307
      , DateTime_year_tooShort             = 308
      , DateTime_year_leadingZero          = 309
      , DateTime_ym_noMonth                = 310
      , DateTime_tz_noUTCsign              = 311
      , DateTime_tz_stuffAfterZ            = 312
      , DateTime_tz_invalid                = 313
      , DateTime_year_zero                 = 314
      , DateTime_mth_invalid               = 315
      , DateTime_day_invalid               = 316
      , DateTime_hour_invalid              = 317
      , DateTime_min_invalid               = 318
      , DateTime_second_invalid            = 319
      , DateTime_tz_hh_invalid             = 320
      , PD_EmptyBase                       = 321
      , PD_NSCompat1                       = 322
      , PD_OccurRangeE                     = 323
      , PD_NameTypeOK1                     = 324
      , PD_NameTypeOK2                     = 325
      , PD_NameTypeOK3                     = 326
      , PD_NameTypeOK4                     = 327
      , PD_NameTypeOK5                     = 328
      , PD_NameTypeOK6                     = 329
      , PD_NameTypeOK7                     = 330
      , PD_Recurse1                        = 331
      , PD_Recurse2                        = 332
      , PD_ForbiddenRes1                   = 333
      , PD_ForbiddenRes2                   = 334
      , PD_ForbiddenRes3                   = 335
      , PD_ForbiddenRes4                   = 336
      , PD_NSSubset1                       = 337
      , PD_NSSubset2                       = 338
      , PD_NSRecurseCheckCardinality1      = 339
      , PD_RecurseUnordered                = 340
      , PD_MapAndSum                       = 341
      , PD_InvalidContentType              = 342
      , NodeIDMap_GrowErr                  = 343
      , XSer_ProtoType_Null_ClassName      = 344
      , XSer_ProtoType_NameLen_Dif         = 345
      , XSer_ProtoType_Name_Dif            = 346
      , XSer_InStream_Read_LT_Req          = 347
      , XSer_InStream_Read_OverFlow        = 348
      , XSer_Storing_Violation             = 349
      , XSer_StoreBuffer_Violation         = 350
      , XSer_LoadPool_UppBnd_Exceed        = 351
      , XSer_LoadPool_NoTally_ObjCnt       = 352
      , XSer_Loading_Violation             = 353
      , XSer_LoadBuffer_Violation          = 354
      , XSer_Inv_ClassIndex                = 355
      , XSer_Inv_checkFillBuffer_Size      = 356
      , XSer_Inv_checkFlushBuffer_Size     = 357
      , XSer_Inv_Null_Pointer              = 358
      , XSer_CreateObject_Fail             = 359
      , XSer_ObjCount_UppBnd_Exceed        = 360
      , XSer_GrammarPool_Empty             = 361
      , XSer_GrammarPool_NotEmpty          = 362
      , XSer_StringPool_NotEmpty           = 363
      , XSer_Storer_Loader_Mismatch        = 364
      , VALUE_QName_Invalid2               = 365
      , F_HighBounds                       = 366
      , E_LowBounds                        = 367
      , E_HighBounds                       = 368
    };


private:
    // -----------------------------------------------------------------------
    //  Unimplemented constructors and operators
    // -----------------------------------------------------------------------
    XMLExcepts();
};

XERCES_CPP_NAMESPACE_END

#endif

