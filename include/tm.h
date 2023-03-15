#ifndef _tm_h_included_
#define _tm_h_included_


#include <vector>
#include <atomic>
#include <string>
#include <time.h>
#include <sstream>
#include "win_types.h"

#define INCL_EQF_TAGTABLE         // tag table and format functions
#define INCL_EQF_TP
#define INCL_EQF_TM
#define INCL_EQF_DAM
#include "EQF.H"

#include "vector"

/*! \brief Data class for the transport of memory proposals
 *
 * 
 */
class OtmProposal
{
  
public:
  //char errorStr[1000];

/*! \brief Constructors */
	OtmProposal();

/*! \brief Destructor */
	~OtmProposal();

  /*! \enum eProposalType
	Proposal types.
*/
	enum eProposalType
	{
		eptUndefined,			/*!< proposal type has not been set or is not available */
		eptManual,	  		/*!< proposal was produced by manual translation */
		eptMachine,	    	/*!< proposal was produced by automatic (machine) translation */
		eptGlobalMemory, 	/*!< proposal is from global memory  */
    eptGlobalMemoryStar /*!< proposal is from global memory, to be marked with an asterisk  */
	};

  /*! \enum eMatchType
	Match types.
*/
	enum eMatchType
	{
		emtUndefined,			/*!< match type has not been set or is not available */
		emtExact,	    		/*!< proposal is an exact match */
		emtExactExact,		/*!< proposal is an exact match, document name and segment number are exact also */
		emtExactSameDoc,	/*!< proposal is an exact match from the same document */
		emtFuzzy,	    		/*!< proposal is a fuzzy match */
		emtReplace 	    	/*!< proposal is a replace match */
	};

  /* operations */

  /* \brief clear all proposal fields 
   */
  void clear();

  /* setters and getters */

   /* \brief get the key of the proposal
     The internal key is the memory internal identifier of the proposal
     \param pszBuffer Pointer to buffer receiving the proposal key
     \param iBufSize Size of the buffer in number of characters
  	 \returns Number of characters copied to pszBuffer including the terminating null character
   */
  int getInternalKey( char *pszBuffer, int iBufSize );
  	
  /* \brief set the proposal key
     \param pszBuffer Pointer to buffer containing the proposal key
   */
  void setInternalKey( char *pszBuffer );
  	

  /* \brief get length of proposal source text 
  	 \returns Number of characters in proposal source text
   */
  int getSourceLen();

  /* \brief get proposal source text 
     \param pszBuffer Pointer to buffer receiving the proposal source text
     \param iBufSize Size of the buffer in number of characters
  	 \returns Number of characters copied to pszBuffer including the terminating null character
   */
  int getSource( wchar_t *pszBuffer, int iBufSize );
  	
  /* \brief set the proposal source text
     \param pszBuffer Pointer to buffer containing the proposal source text
   */
  void setSource( wchar_t *pszBuffer );

  /* \brief get length of proposal target text 
  	 \returns Number of characters in proposal target text
   */
  int getTargetLen();

  /* \brief get proposal target text   
     \param pszBuffer Pointer to buffer receiving the proposal target text
     \param iBufSize Size of the buffer in number of characters
  	 \returns Number of characters copied to pszBuffer including the terminating null character
   */
  int getTarget( wchar_t *pszBuffer, int iBufSize );
  	
  /* \brief set the proposal target text
     \param pszBuffer Pointer to buffer containing the proposal target text
   */
  void setTarget( wchar_t *pszBuffer );
  	
  /* \brief get proposal ID
     \param pszBuffer Pointer to buffer receiving the proposal ID
     \param iBufSize Size of the buffer in number of characters
     \returns Number of characters copied to pszBuffer including the terminating null character
   */
  int getID( char *pszBuffer, int iBufSize );
  	
  /* \brief set the proposal ID 
     \param pszBuffer Pointer to buffer containing the proposal ID
   */
  void setID( char *pszBuffer );
  	

  /* \brief get proposal document name

    \param pszBuffer Pointer to buffer receiving the document name
    \param iBufSize Size of the buffer in number of characters
  	\returns Number of characters copied to pszBuffer including the terminating null character
   */
  int getDocName( char *pszBuffer, int iBufSize );
  	
  /* \brief set the proposal document short name
     \param pszBuffer Pointer to buffer containing the document name
   */
  void setDocName( char *pszBuffer );
  	
  /* \brief get proposal document short name
     \param pszBuffer Pointer to buffer receiving the document short name
     \param iBufSize Size of the buffer in number of characters
  	 \returns Number of characters copied to pszBuffer including the terminating null character
   */
  int getDocShortName( char *pszBuffer, int iBufSize );
  	
  /* \brief set the proposal document short name
     \param pszBuffer Pointer to buffer containing the document short short name
   */
  void setDocShortName( char *pszBuffer );

  /* \brief get proposal segment number
   	\returns proposal segment number
   */
  long getSegmentNum();
  	
  /* \brief set the proposal segment number
     \param lSegmentNum new segment number of proposal
   */
  void setSegmentNum( long lSegmentNum );
  	
  /* \brief get proposal source language
     \param pszBuffer Pointer to buffer receiving the proposal source language
     \param iBufSize Size of the buffer in number of characters
  	 \returns Number of characters copied to pszBuffer including the terminating null character
   */
  int getSourceLanguage( char *pszBuffer, int iBufSize );
  int getOriginalSourceLanguage( char* pszBuffer, int iBufSize );
  /* \brief set the proposal source language
     \param pszBuffer Pointer to buffer containing the proposal source language
   */
  void setSourceLanguage( char *pszBuffer );
  void setOriginalSourceLanguage( char* pszBuffer);

  /* \brief get proposal target language
     \param pszBuffer Pointer to buffer receiving the proposal target language
     \param iBufSize Size of the buffer in number of characters
  	 \returns Number of characters copied to pszBuffer including the terminating null character
   */
  int getTargetLanguage( char *pszBuffer, int iBufSize );
  	
  /* \brief set the proposal target language
     \param pszBuffer Pointer to buffer containing the proposal target language
   */
  void setTargetLanguage( char *pszBuffer );

  /* \brief get proposal type
     \returns proposal type
   */
  eProposalType getType();
  	
  /* \brief set the proposal type
     \param eType new type of the proposal
   */
  void setType( eProposalType eType );

  /* \brief get match type
     \returns proposal type
   */
  eMatchType getMatchType();
  	
  /* \brief set the match type
     \param eType new type of the proposal
   */
  void setMatchType( eMatchType eType );

  /* \brief get name of proposal author
     \param pszBuffer Pointer to buffer receiving the name of the proposal author
     \param iBufSize Size of the buffer in number of characters
     \returns Number of characters copied to pszBuffer including the terminating null character
   */
  int getAuthor( char *pszBuffer, int iBufSize );
  	
  /* \brief set the name of the proposal author
     \param pszBuffer Pointer to buffer containing the name of the proposal author
   */
  void setAuthor( char *pszBuffer );

  /* \brief get proposal time stamp
     \returns proposal segment number
   */
  long getUpdateTime();
  	
  /* \brief set the proposal time stamp
     \param lTime new time stamp of proposal
   */
  void setUpdateTime( long lSegmentNum );

  /* \brief get proposal fuzziness
     \returns proposal fuzziness
   */
  int getFuzziness();

  /* \brief set the proposal fuzziness
     \param lFuzzinessTime new fuzziness of proposal
   */
  void setFuzziness( long iFuzziness );

  /* \brief get proposal diffs count from fuzzy calculations
    \returns proposal diffs count from fuzzy calculations
  */
  int getDiffs();

  /* \brief set the proposal diffs count from fuzzy calculations
     \param iDiffs new diffs count from fuzzy calculations of proposal
   */
  void setDiffs( long iDiffs );

    /* \brief get proposal words count during fuzzy calculations
     \returns proposal fuzziness
   */
  int getWords();

  /* \brief set the proposal words count during fuzzy calculations
     \param iWords new words count during fuzzy calculations of proposal
   */
  void setWords( long iWords );

  /* \brief get markup table name (format)
     \param pszBuffer Pointer to buffer receiving the name of the markup table name
     \param iBufSize Size of the buffer in number of characters
     \returns Number of characters copied to pszBuffer including the terminating null character
   */
  int getMarkup( char *pszBuffer, int iBufSize );
  	
  /* \brief set markup table name (format)
     \param pszBuffer Pointer to buffer containing the markup table name
   */
  void setMarkup( char *pszBuffer );

  /* \brief get length of proposal context
  	 \returns Number of characters in proposal context
   */
  int getContextLen();

  /* \brief get proposal Context 
     \param pszBuffer Pointer to buffer receiving the proposal context
     \param iBufSize Size of the buffer in number of characters
  	 \returns Number of characters copied to pszBuffer including the terminating null character
   */
  int getContext( wchar_t *pszBuffer, int iBufSize );
  	
  /* \brief set the proposal context
     \param pszBuffer Pointer to buffer containing the proposal context
   */
  void setContext( wchar_t *pszBuffer );

  /* \brief get proposal context ranking
  	\returns proposal context ranking
   */
  int getContextRanking();
  	
  /* \brief set the proposal context ranking
     \param iContextRanking context ranking for the proposal (0..100)
   */
  void setContextRanking( int iContextRanking );

  /* \brief get length of proposal AddInfo text 
  	 \returns Number of characters in proposal AddInfo text
   */
  int getAddInfoLen();

  /* \brief get additional info
     \param pszBuffer Pointer to buffer receiving the additional info
     \param iBufSize Size of the buffer in number of characters
  	 \returns Number of characters copied to pszBuffer including the terminating null character
   */
  int getAddInfo( wchar_t *pszBuffer, int iBufSize );
  	
  /* \brief set the proposal additional information
     \param pszBuffer Pointer to buffer containing the additional info
   */
  void setAddInfo( wchar_t *pszBuffer );

  /* \brief set the proposal memory index
     \param iIndex new value for the memory index
  */
  void setMemoryIndex( int iIndex );

  /* \brief get memory index
     \returns memory index of this proposal
  */
  int getMemoryIndex();

  /* \brief set the DITA replacement list
     \param pList new value for the DITA replacement list
  */
  void setReplacementList( long pList );

  /* \brief get DITA replacement list
     \returns pointer to DITA replacement list
  */
  long getReplacementList();

  /* \brief check if proposal match type is one of the exact match types
   */
  bool isExactMatch();

  /* \brief check if proposal is empty (i.e. has not been used)
   */
  bool isEmpty();

  bool isSourceLangIsPrefered();
  void setIsSourceLangIsPrefered(bool fPref);
  /* \brief check if source and target of proposal is equal
   */
  bool isSourceAndTargetEqual();

  /* \brief check if target strings are identical
     \param otherProposal pointer to second proposal 
  */
  bool isSameTarget( OtmProposal *otherProposal );

  /*! \brief Clear the data of proposals stored in a vector
      \param Proposals reference to a vector containing the proposals
  */
  void static clearAllProposals(
    std::vector<OtmProposal *> &Proposals
  );

  /*! \brief Get the number of filled proposals in a proposal list
      \param Proposals reference to a vector containing the proposals
  */
  int static getNumOfProposals(
    std::vector<OtmProposal *> &Proposals
  );


  /* \brief assignment operator to copy the datafields from one
    OtmProposal to another one
     \param copyme reference to OtmProposal being copied
   */
  OtmProposal &operator=( const OtmProposal &copyme );


private:

  /* \brief private proposal data */
	void *pvProposalData; 
};



/*! \brief Abstract base-class for translation memory objects */
class OtmMemory
{

public:

/*! \brief Constructors */
	OtmMemory() {};
	
 
/*! \brief Destructor */
	virtual ~OtmMemory() {};

/*! \brief Error code definition
*/
  static const int ERROR_NOSHAREDMEMORYPLUGIN = 8001;
  static const int ERROR_PROPERTYLOADFAILED   = 8002;
  static const int ERROR_MEMORYOBJECTISNULL   = 8003;
  static const int ERROR_BUFFERTOOSMALL       = 8004;
  static const int ERROR_INVALIDOBJNAME       = 8005;
  static const int ERROR_MEMORYEXISTS         = 8006;
  static const int ERROR_INVALIDREQUEST       = 8007;
  static const int INFO_ENDREACHED            = 8008;
  static const int ERROR_ENTRYISCORRUPTED     = 8009;

/*! \brief Provide a list of memory proposals matching the given search key

    This method uses the search data contained in the search key to find one or more
    matching proposals in the memory. At least the szSource and the szTargetLang members of the
    search key have to be filled by the caller.
    The caller provides a list of OtmProposals which will be filled with the data of the matching 
    proposals. The number of requested proposals is determined by the number
    of proposals in the list.

    \param SearchKey proposal containing search string and meta data
    \param FoundProposals refernce to vector with OtmProposal objects
    \param ulOptions options for the lookup

  	\returns 0 or error code in case of errors
*/
  virtual int searchProposal
  (
    OtmProposal &SearchKey,
    std::vector<OtmProposal *> &FoundProposals,
    unsigned long ulOptions

  ) = 0; 

/*! \brief Get the the first proposal from the memory and prepare sequential access
    \param Proposal reference to a OtmProposal object which will be filled with the proposal data
  	\returns 0 or error code in case of errors
*/
  virtual int getFirstProposal
  (
    OtmProposal &Proposal
  ) = 0; 

/*! \brief Get the the first proposal from the memory and prepare sequential access
    \param Proposal reference to a OtmProposal object which will be filled with the proposal data
    \param piProgress pointer to buffer for progress indicator, this indicator goes from 0 up to 100
  	\returns 0 or error code in case of errors
*/
  virtual int getFirstProposal
  (
    OtmProposal &Proposal,
    int *piProgress
  ) = 0; 

/*! \brief Get the the proposal having the supplied key (InternalKey from the OtmProposal)
    \param pszKey internal key of the proposal
    \param Proposal buffer for the returned proposal data
  	\returns 0 or error code in case of errors
*/
  virtual int getProposal
  (
    char *pszKey,
    OtmProposal &Proposal
  ) = 0; 

/*! \brief Get the next proposal from the memory 
    \param lHandle the hande returned by GetFirstProposal
    \param Proposal reference to a OtmProposal object which will be filled with the proposal data
  	\returns 0 or error code in case of errors
*/
  virtual int getNextProposal
  (
    OtmProposal &Proposal
  ) = 0; 

/*! \brief Get the next proposal from the memory 
    \param Proposal reference to a OtmProposal object which will be filled with the proposal data
    \param piProgress pointer to buffer for progress indicator, this indicator goes from 0 up to 100
  	\returns 0 if a proposal was returned, ENDREACHED when the end of the memory has been reached or an error code in case of errors
*/
  virtual int getNextProposal
  (
    OtmProposal &Proposal,
    int *piProgress
  ) = 0; 

  /*! \brief Get the current sequential access key (the key for the next proposal in the memory) 
    \param pszKeyBuffer pointer to the buffer to store the sequential access key
    \param iKeyBufferSize size of the key buffer in number of characters
  	\returns 0 or error code in case of errors
  */
  virtual int getSequentialAccessKey
  (
    char *pszKeyBuffer,
    int  iKeyBufferSize
  ) = 0; 

    
  /*! \brief Set the current sequential access key to resume the sequential access at the given position
    \param pszKey a sequential access key previously returned by getSequentialAccessKey
  	\returns 0 or error code in case of errors
  */
  virtual int setSequentialAccessKey
  (
    char *pszKey
  ) = 0; 

/*! \brief Store the supplied proposal in the memory
    When the proposal aready exists it will be overwritten with the supplied data

    \param pProposal pointer to a OtmProposal object

  	\returns 0 or error code in case of errors
*/
  virtual int putProposal
  (
    OtmProposal &Proposal
  ) = 0; 


  /*! \brief Rebuild internal index after mass updates
    This method is called after mass updates (e.g. memory import) has beebn performed.
    The memory can rebuild or optimize its internal index when necessary.

  	\returns 0 or error code in case of errors
*/
  virtual int rebuildIndex
  (
  ) = 0; 

/*! \brief Flags for the update of proposals */

static const int UPDATE_MARKUP   = 0x01;           // update markup/tag table
static const int UPDATE_MTFLAG   = 0x02;           // update machine translation flag
static const int UPDATE_TARGLANG = 0x04;           // update target language
static const int UPDATE_DATE     = 0x08;           // update proposal update time

/*! \brief Updates some fields of a specific proposal in the memory

    \param Proposal reference to a OtmProposal object containing the data being changed
    \param usUpdateFlags Flags selecting the update fields

  	\returns 0 or error code in case of errors
*/
  virtual int updateProposal
  (
    OtmProposal &Proposal,
    USHORT      usUpdateFlags
  ) = 0; 

/*! \brief Delete a specific proposal from the memory

    \param Proposal reference to a OtmProposal object

  	\returns 0 or error code in case of errors
*/
  virtual int deleteProposal
  (
    OtmProposal &Proposal
  ) = 0; 


/*! \brief Data area for the getMemoryPart method */
typedef struct _MEMORYPARTDATA
{
  // fields provided and filled by the caller of the method
  BOOL   fFirstCall;                   // TRUE = this is the initial call for this memory file, FALSE = a subsequent call
  char   szFileName[MAX_LONGFILESPEC]; // name of file being processed currently (the file name is from the list of memory data files
                                       // provided using the getMemoryFiles method
  PBYTE  pbBuffer;                     // points to the buffer for the provided data
  ULONG  ulBytesToRead;                // number of bytes to be copied to buffer

  // data fields filled by the getMemoryPart method
  BOOL   fFileIsComplete;              // TRUE = the data of the current file has been stored in the buffer completely, 
                                       // FALSE = there is more data coming
  ULONG  ulBytesRead;                  // length of data stored in the buffer in number of bytes

  // private data fields for the getMemoryPart method (this data is not used by the calling function in any way)
  ULONG  ulFilePos;                    // could be used for the read position in current file
  ULONG  ulRemaining;                  // could be used for the number of bytes remaining
  ULONG  ulTotalSize;                  // could be used for the total size of the current file
  ULONG  ulState;                      // could be used for current processing state
  void   *pPrivatData;                 // could be used as anchor for private data areas
  char   chPrivateBuffer[1024];        // could be used as private buffer area
} MEMORYPARTDATA, *PMEMORYPARTDATA;

/*! \brief Provides part of a memory data file in binary format

     The binary format is used by the folder export to add the memory
     in the internal format to the exported folder.

    \param pMemoryPartData pointer to the data area for the extraxt om binary format

  	\returns 0 or error code in case of errors
*/
  virtual int getMemoryPart
  (
    PMEMORYPARTDATA pData           // points to data area supplied by the caller
  ) = 0;

/*! \brief Get the name of the memory
    \param pszBuffer pointer to a buffer for the name
    \param iSize size of buffer in number of characters
  	\returns number of characters copied to the buffer
*/
  virtual int getName
  (
    char *pszBuffer,
    int iSize
  ) = 0;

/*! \brief Get the name of the memory
    \param strName reference of a string receiving the memory name
*/
  virtual int getName
  (
    std::string &strName
  ) = 0;



/*! \brief Get number of markups used for the proposals in this mmoryProvides a part of the memory in binary format
  	\returns number of markups used by the memory proposals or 0 if no markup information can be provided
*/
  virtual int getNumOfMarkupNames() = 0;

/*! \brief Get markup name at position n [n = 0.. GetNumOfMarkupNames()-1]
    \param iPos position of markup table name
    \param pszBuffer pointer to a buffer for the markup table name
    \param iSize size of buffer in number of characters
  	\returns number of characters copied to buffer
*/
  virtual int getMarkupName
  (
    int iPos,
    char *pszBuffer,
    int iSize
  ) = 0;

/*! \brief Get source language of the memory
    \param pszBuffer pointer to a buffer for the source language name
    \param iSize size of buffer in number of characters
  	\returns number of characters copied to the buffer
*/
  virtual int getSourceLanguage
  (
    char *pszBuffer,
    int iSize
  ) = 0;

/*! \brief Get description of the memory
    \param pszBuffer pointer to a buffer for the description
    \param iSize size of buffer in number of characters
  	\returns number of characters copied to the buffer
*/
  virtual int getDescription
  (
    char *pszBuffer,
    int iSize
  ) = 0;

/*! \brief Set the description of the memory
    \param pszBuffer pointer to the description text
*/
  virtual void setDescription
  (
    char *pszBuffer
  ) = 0;


/*! \brief Get plugin responsible for this memory
  	\returns pointer to memory plugin object
*/
  virtual void *getPlugin() = 0;

/*! \brief Get number of proposals in thismemory
  	\returns number of proposals
*/
  virtual unsigned long getProposalNum() = 0;

/*! \brief Get overall file size of this memory
  	\returns size of memory in number of bytes
*/
  virtual unsigned long getFileSize() = 0;



/*! \brief OtmMemory related return codes

*/
  static const int ERROR_INTERNALKEY_MISSING = 1001;

/*! \brief Get the error message for the last error occured

    \param strError reference to a string receiving the error mesage text
  	\returns last error code
*/
	virtual int getLastError
  (
    std::string &strError
  ) = 0; 
/*! \brief Get the error message for the last error occured

    \param pszError pointer to a buffer for the error text
    \param iBufSize size of error text buffer in number of characters
  	\returns last error code
*/
	virtual int getLastError
  (
    char *pszError,
    int iBufSize
  ) = 0; 

/*! \brief Get number of different document names used in the memory
  	\returns number of document used by the memory proposals or 0 if no document name information can be provided
*/
  	virtual int getNumOfDocumentNames() = 0;

/*! \brief Get document name at position n [n = 0.. GetNumOfDocumentNames()-1]
    \param iPos position of document name
    \param pszBuffer pointer to a buffer for the document name
    \param iSize size of buffer in number of characters
  	\returns number of characters copied to buffer
*/
  	virtual int getDocumentName
    (
      int iPos,
      char *pszBuffer,
      int iSize
    ) = 0;

/*! \brief Get number of different document short names used in the memory
  	\returns number of document short names used by the memory proposals or 0 if no document short name information can be provided
*/
  	virtual int getNumOfDocumentShortNames() = 0;

/*! \brief Get document name at position n [n = 0.. GetNumOfDocumentNames()-1]
    \param iPos position of document name
    \param pszBuffer pointer to a buffer for the document name
    \param iSize size of buffer in number of characters
  	\returns number of characters copied to buffer
*/
  	virtual int getDocumentShortName
    (
      int iPos,
      char *pszBuffer,
      int iSize
    ) = 0;

/*! \brief Get number of different languages used in the memory
  	\returns number of languages used by the memory proposals or 0 if no language information can be provided
*/
  	virtual int getNumOfLanguages() = 0;

/*! \brief Get language at position n [n = 0.. GetNumOfLanguages()-1]
    \param iPos position of language
    \param pszBuffer pointer to a buffer for the document name
    \param iSize size of buffer in number of characters
  	\returns number of characters copied to buffer
*/
  	virtual int getLanguage
    (
      int iPos,
      char *pszBuffer,
      int iSize
    ) = 0;
	
/*! \brief Set or clear the pointer to a loaded global memory option file

    This method sets a pointer to a loaded global memory option file.
    When set the option file will be used to decide how global memory proposals will be processed.

    \param pvGlobalMemoryOptions pointer to a loaded global memory option file or NULL to clear the current option file pointer

  	\returns 0 or error code in case of errors
*/
  virtual int setGlobalMemoryOptions
  (
    void *pvGlobalMemoryOptions
  ) = 0; 
  

private:

};


/*! \brief memory proposal types */
	enum MemProposalType
	{
		UNDEFINED_PROPTYPE,			/*!< proposal type has not been set or is not available */
		MANUAL_PROPTYPE,	  		/*!< proposal was produced by manual translation */
		MACHINE_PROPTYPE,	    	/*!< proposal was produced by automatic (machine) translation */
		GLOBMEMORY_PROPTYPE, 	  /*!< proposal is from global memory  */
    GLOBMEMORYSTAR_PROPTYPE /*!< proposal is from global memory, to be marked with an asterisk  */
	};

/*! \brief match type of memory proposals */
	enum MemProposalMatchType
	{
		UNDEFINED_MATCHTYPE,			/*!< match type has not been set or is not available */
		EXACT_MATCHTYPE,	    		/*!< proposal is an exact match */
		EXACTEXACT_MATCHTYPE,		/*!< proposal is an exact match, document name and segment number are exact also */
		EXACTSAMEDOC_MATCHTYPE,	/*!< proposal is an exact match from the same document */
		FUZZY_MATCHTYPE,	    		/*!< proposal is a fuzzy match */
		REPLACE_MATCHTYPE 	    	/*!< proposal is a replace match */
	};

/*! \brief maximum size of segment data */
#define MEMPROPOSAL_MAXSEGLEN 2048

/*! \brief maximum size of names */
#define MEMPROPOSAL_MAXNAMELEN 256


/*! \brief Structure for sending or receiving memory proposal data
*/
typedef struct _MEMPROPOSAL
{
  /*! \brief ID of this proposal */
	char szId[MEMPROPOSAL_MAXNAMELEN];

  /*! \brief Source string of memory proposal  (UTF-16) */
  wchar_t szSource[MEMPROPOSAL_MAXSEGLEN+1];
	//std::wstring strSource;

	/*! \brief Target string of memory proposal (UTF-16). */
  wchar_t szTarget[MEMPROPOSAL_MAXSEGLEN+1];

	/*! \brief Name of document from which the proposal comes from. */
	char szDocName[MEMPROPOSAL_MAXNAMELEN];

	/*! \brief Short (8.3) name of the document from which the proposal comes from. */
	//std::string strDocShortName;
	char szDocShortName[MEMPROPOSAL_MAXNAMELEN];

	/*! \brief Segment number within the document from which the proposal comes from. */
  long lSegmentNum;                  

	/*! \brief source language. */
	char szSourceLanguage[MEMPROPOSAL_MAXNAMELEN];

	/*! \brief target language. */
  char szTargetLanguage[MEMPROPOSAL_MAXNAMELEN];

	/*! \brief origin or type of the proposal. */
  MemProposalType eType;

	/*! \brief match type of the proposal. */
  MemProposalMatchType eMatch;

	/*! \brief Author of the proposal. */
  char szTargetAuthor[MEMPROPOSAL_MAXNAMELEN];

	/*! \brief Update time stamp of the proposal. */
  long    lTargetTime;

	/*! \brief Fuzziness of the proposal. */
  int iFuzziness;    

  /*! \brief Words parsed in fuzzy calculations of the proposal. */
  int iWords = -1;

  /*! \brief Diffs in fuzzy calculations of the proposal. */
  int iDiffs = -1;                 

	/*! \brief Markup table (format) of the proposal. */
  char szMarkup[MEMPROPOSAL_MAXNAMELEN];

  /*! \brief Context information of the proposal */
  //std::wstring strContext;  
  wchar_t szContext[MEMPROPOSAL_MAXSEGLEN+1];

  /*! \brief Additional information of the proposal */
  //std::wstring strAddInfo; 
  wchar_t szAddInfo[MEMPROPOSAL_MAXSEGLEN+1];
  
  /*! \brief is source lang is marked as prefered in languages.xml */
  bool fIsoSourceLangIsPrefered = false;
  /*! \brief is target lang is marked as prefered in languages.xml */
  bool fIsoTargetLangIsPrefered = false;

} MEMPROPOSAL, *PMEMPROPOSAL;

//#include "../pluginmanager/PluginManager.h"

#include "EQF.H"

// ************ Translation memory flags ********************************
#define far

#define  MEM_OUTPUT_ASIS          0   // Do not convert translation memory output
#define  MEM_OUTPUT_CRLF          1   // Convert translation memory output to CRLF
#define  MEM_OUTPUT_LF            2    // Convert translation memory output to LF

// defines for special names mode of TMExtract (only valid with TMExtract!)
#define  MEM_OUTPUT_TAGTABLES     3   // return list of tag tables of TM
#define  MEM_OUTPUT_AUTHORS       4   // return list of authors of TM
#define  MEM_OUTPUT_DOCUMENTS     5   // return list of documents of TM
#define  MEM_OUTPUT_LANGUAGES     6   // return list of languages of TM
#define  MEM_OUTPUT_LONGNAMES     7   // return list of document long names of TM
#define  MEM_OUTPUT_ALLDOCS       8   // return list of all documensts (long
                                      // names and short names for docs w/o long name)

#define EXCLUSIVE               0
#define NONEXCLUSIVE            1
#define EXCLUSIVE_FOR_GET_PART  2
#define FOR_ORGANIZE            3
#define READONLYACCESS          4

// defines used in TmOpen and MemCreateDlg
#define  TM_LOCAL                  0     // TM resides local
#define  TM_REMOTE                 1     // TM resides remote on a server
#define  TM_LOCALREMOTE            2     // TM may be local or remote
#define  TM_SHARED                 3     // TM resides on a shared drive

//  Match value constants: the similarity level classes   (lSimLevel)
#define BASE_SIMILAR          0L
#define BASE_EXACT_DATE       200L
#define BASE_EXACT_IND        300L
#define BASE_EXACT_SEG_NUM    400L

#define MAX_SIMILAR_VAL       100L
#define MAX_EXACT_DATE_VAL    (BASE_EXACT_IND - 1L)
#define MAX_EXACT_IND_VAL     (BASE_EXACT_SEG_NUM - 1L)
#define MAX_EXACT_SEG_NUM_VAL (500L - 1L)

#define EXTENT_SIMILAR        (MAX_SIMILAR_VAL - BASE_SIMILAR)
#define EXTENT_EXACT_DATE     (MAX_EXACT_DATE_VAL - BASE_EXACT_DATE)
#define EXTENT_EXACT_IND      (MAX_EXACT_IND_VAL - BASE_EXACT_IND)
#define EXTENT_EXACT_SEG_NUM  (MAX_EXACT_SEG_NUM_VAL - BASE_EXACT_SEG_NUM)

// translation flag values
#define TRANSLFLAG_NORMAL      0
#define TRANSLFLAG_MACHINE     1
#define TRANSLFLAG_GLOBMEM     2
#define TRANSLFLAG_GLOBMEMSTAR 3


/*----------------------------------------------------------------------------*\
  System wide threshold values
\*----------------------------------------------------------------------------*/
#define LENGTH_THR         50L  // Length threshold value
#define MAX_LENGTH_THR    100L  // maximal Length threshold value
#define INIT_MATCH_THR     59L  // Initial match threshold value
#define SHORTER_MATCH_THR  50L  // match threshold value for shorter
                                // segments, defined thru LENGTH_SHORTER_VALUE
#define WORDS_MATCH_THR 0L      // Not used yet

//--- Used in GET_IN structure to specify kind of matches.
//--- This defines should be bitwise 'ored' with the number of required matches.
//--- GET_EXACT means if at least one exact match is found return only exact
//--- matches. GET_EXACT_AND_FUZZY means return exact and fuzzy matches.
//--- Example pGetIn->usNumMatchesReq = 3 | GET_EXACT_AND_FUZZY
//--- If only the number of required matches is passed, GET_EXACT is used.
//--- If you want to retrieve translation memory hits with exact context only,
//--- use GET_EXACT_CONTEXT.
//--- If Generic replace should be disabled, you have to or with GET_NO_GENERICREPLACE
#define GET_MOREPROP_INDIC     0x00000200
#define GET_ALL_EXACT_MATCHES  0x00000400
#define GET_RESPECTCRLF        0x00000800
#define GET_IGNORE_PATH        0x00001000
#define GET_NO_GENERICREPLACE  0x00002000
#define GET_EXACT_AND_CONTEXT  0x00004000
#define GET_EXACT_AND_FUZZY    0x00008000
#define GET_ALWAYS_WITH_TAGS   0x00010000
#define GET_IGNORE_COMMENT     0x00020000
#define GET_EXACT              0x00040000

#define EQUAL_EQUAL              100
#define TAGS_EQUAL               98
#define TAGS_UNEQUAL             95

#define NON_EXCLUSIVE       1
#define EXCLUSIVE           0

#define LANG_KEY            1L
#define FILE_KEY            2L
#define AUTHOR_KEY          3L
#define TAGTABLE_KEY        4L
//#define RESERVED_KEY        5L
#define LONGNAME_KEY        5L
#define COMPACT_KEY         6L
#define FIRST_KEY           7L
// Note: the following key is NOT used as the key of a QDAM record
//       it is only a symbolic value used in the Name-to-ID functions
#define LANGGROUP_KEY       8L


// used in GET_OUT structure
#define GET_MORE_EXACTS_AVAIL      0x8000
#define GET_ADDITIONAL_FUZZY_AVAIL 0x4000

/**********************************************************************/
/* Return Codes                                                       */
/**********************************************************************/
#define TMERR_BASE ERR_MEM_BASE            /* Base for errors          */

#define TMERR_EOF     TMERR_BASE + 12

#define DISK_FULL     TMERR_BASE + 13   // for Add /Replace / Create
#define DB_FULL       TMERR_BASE + 14   // when number of blocks exceeds 2**16 - 1

#define SEG_NOT_FOUND TMERR_BASE + 20   /* for Delete command          */
#define CLUSTER_EMPTY TMERR_BASE + 21   /* Internally only             */

#define TM_FILE_NOT_FOUND                  TMERR_BASE + 30 // for Open
#define FILE_ALREADY_OPEN                  TMERR_BASE + 31 // for Open
#define CORRUPTION_FLAG_ON                 TMERR_BASE + 32 // for Open
#define FILE_MIGHT_BE_CORRUPTED            TMERR_BASE + 33 // for Open
#define VERSION_MISMATCH                   TMERR_BASE + 34 // for Open
#define CORRUPT_VERSION_MISMATCH           TMERR_BASE + 35 // for Open
#define TM_FILE_SCREWED_UP                 TMERR_BASE + 36 // for Open
#define NOT_A_MEMORY_DATABASE              TMERR_BASE + 37 // for Open
// the following error code is returned if open fails because a TM was
// corrupted and (on confirmation via a message) was then
// successfully organized
#define TM_WAS_CORRUPTED_IS_ORGANIZED      TMERR_BASE + 38 // for Open,
#define TM_PROPERTIES_DIFFERENT            TMERR_BASE + 39 // for Open,
#define SERVER_DRIVE_REMOVED               TMERR_BASE + 40 // for Open, /*@89A*/
#define SERVER_DRIVE_ACTIVE                TMERR_BASE + 41 // for Open, /*@89A*/
#define TM_PROPERTIES_EQUAL                TMERR_BASE + 42 // for Open,/*@1170A*/
#define TM_PROPERTIES_NOT_OPENED           TMERR_BASE + 43 // for Open,/*@1170A*/

#define BLOCK_SIZE_TOO_SMALL     TMERR_BASE + 48 /* for Create         */
#define FILE_ALREADY_EXISTS      TMERR_BASE + 49 /* for Create         */

#define NO_SEG_FOUND             TMERR_BASE + 50 /* for Extract        */

#define ILLEGAL_TM_COMMAND       TMERR_BASE + 60 /* for TMT            */

#define NOT_REPLACED_OLD_SEGMENT TMERR_BASE + 70 /* for Replace        */
#define SEGMENT_BUFFER_FULL      TMERR_BASE + 71 /* for Replace   */ /*@1108A*/
                                         /*rc from AddSegToCluster*/ /*@1108A*/
#define SEG_SKIPPED_BAD_MARKUP   TMERR_BASE + 72 /* for Import         */
#define SEG_RESET_BAD_MARKUP     TMERR_BASE + 73 /* for Import         */

#define TM_FUNCTION_FAILED       TMERR_BASE + 80 /* Undefinable Error  */

// Currently not used
//#define TMERR_TM_HANDLER_ALREADY_ACTIVE     TMERR_BASE + 90  // Comm code

#define TMERR_TOO_MANY_OPEN_DATABASES       TMERR_BASE + 91  // Comm code
#define TMERR_TOO_MANY_USERS_CONNECTED      TMERR_BASE + 92  // Comm code
#define TMERR_THREAD_NOT_SPAWNED            TMERR_BASE + 93  // Comm code
#define TMERR_TM_OPENED_EXCLUSIVELY         TMERR_BASE + 94  // Comm code
#define TMERR_TM_OPENED_SHARED              TMERR_BASE + 95  // Comm code

// Currently not used
//#define TMERR_PIPE_EXISTS                   TMERR_BASE + 96  // Comm code

#define TMERR_NO_MORE_MEMORY_AVAILABLE      TMERR_BASE + 97  // Comm code
#define TMERR_THREAD_INIT_FAILED            TMERR_BASE + 98  // Comm code
#define TMERR_TOO_MANY_QUERIES              TMERR_BASE + 99  // Comm code
#define TMERR_PROP_EXIST                    TMERR_BASE + 100 // Comm code
#define TMERR_PROP_WRITE_ERROR              TMERR_BASE + 101 // Comm code
#define TMERR_PROP_NOT_FOUND                TMERR_BASE + 102 // Comm code
#define TMERR_PROP_READ_ERROR               TMERR_BASE + 103 // Comm code
#define TMERR_TOO_MANY_TMS                  TMERR_BASE + 104 // Comm code
#define TMERR_SERVER_NOT_STARTED            TMERR_BASE + 105 // Comm code
#define TMERR_SERVERCODE_NOT_STARTED        TMERR_BASE + 106 // Comm code
#define TMERR_COMMUNICATION_FAILURE         TMERR_BASE + 107 // Comm code

// This error code is sent when somebody stops the server code and open connections
// are still there (it's not guaranteed that this error code makes it to the requester
// since the pipe is closed immediately; if this error code doesn't make it to the
// requester, TMERR_COMMUNICATION_FAILURE will be returned)
#define TMERR_SERVER_ABOUT_TO_EXIT          TMERR_BASE + 108 // Comm code
#define TMERR_TOO_MANY_USERS_ON_SERVER      TMERR_BASE + 109 // Comm code

#define SOURCE_STRING_ERROR                 TMERR_BASE + 150
#define ERROR_ADD_TO_TM                     TMERR_BASE + 151

#define LANG_FILE_NOT_FOUND                 TMERR_BASE + 200 // for Create
#define LANGUAGE_NOT_FOUND                  TMERR_BASE + 201 // for Create
#define LANG_FILE_LINE_TOO_LONG             TMERR_BASE + 202 // for Create
#define LANG_CHAR_APPEARS_TWICE             TMERR_BASE + 203 // for Create
#define LANG_GROUP_NUM_TOO_LARGE            TMERR_BASE + 204 // for Create
#define TAG_FILE_NOT_FOUND                  TMERR_BASE + 205 // for Create
#define WORD_FILE_NOT_FOUND                 TMERR_BASE + 206 // for Create
#define TAG_FILE_TOO_LARGE                  TMERR_BASE + 207 // for Create /*@ZDA*/
#define ERROR_OLD_PROPERTY_FILE             TMERR_BASE + 208
#define ERROR_REMOTE_TM_NOT_SUPPORTED       TMERR_BASE + 209
#define ERROR_VERSION_NOT_SUPPORTED         TMERR_BASE + 210

#define  MEM_PROCESS_OK        6900              // Return code of load is OK
#define  MEM_READ_ERR          MEM_PROCESS_OK+1  // Dos read error
#define  MEM_WRITE_ERR         MEM_PROCESS_OK+2  // Dos write error
#define  MEM_SEG_SYN_ERR       MEM_PROCESS_OK+3  // Segment syntax error
#define  MEM_FILE_SYN_ERR      MEM_PROCESS_OK+4  // File syntax error
#define  MEM_LOAD_OK           MEM_PROCESS_OK+5  // Return code of load dialog is OK
#define  MEM_PROCESS_END       MEM_PROCESS_OK+6  // ID which indicates that a proc is terminated
#define  MEM_DB_ERROR          MEM_PROCESS_OK+7  // Unpredictable memory db error
#define  MEM_DB_CANCEL         MEM_PROCESS_OK+8  // load process was canceled /*@47*/
#define  MEM_DB_CANCEL         MEM_PROCESS_OK+8  // load process was canceled /*@47*/
#define  MEM_DB_EXTRACT_ERROR  MEM_PROCESS_OK+9  // retuned from function MemReadWriteSegment when TmExtract fails /*@47*/
#define  MEM_DB_REPLACE_ERROR  MEM_PROCESS_OK+10 // retuned from function MemReadWriteSegment when TmReplace fails /*@47*/

/* The segment marker */
#define  SEGMARKER       "###"

#define KEY_DIR_SIZE         4096  // key directory size
#define TM_PREFIX_SIZE          8  // length of prefix bytes in TMT db
#define MAX_SEC_LENGTH       30        // max length of secondary key
#define MAX_LINE_LENGTH      80        // max length of each line in lang file
#define FN_LENGTH            13        // length of input filename
#define PRIM_KEY_LENGTH       4        // number of characters in primary key
#define DATA_IN_SIZE       3900        // buffer size for input
#define DATA_OUT_SIZE      3900        // buffer size for output
#define CODEPAGE_SIZE       256        // size of codepage of the language
#define SEG_MARKER_LENGTH     3        // length of segment marker
#define MAX_TGT_LENGTH     2047        // max length of each target.
#define MAX_MATCH_TAB_ENTRIES 5        // number of entries in match table
#define CREATE_BUFFER_SIZE   40000     // buffer size for create_in
#define MAX_TM_LIST_NUMBER    500      // max. number of TMs that can be listed
                                       // by the TMC_GET_SERVER_TM_LIST command
#define GETPART_BUFFER_SIZE 16384      // read a 16 KB block at a time
#define MEM_PROP_SIZE    2048          // Global size of all memory database properties
#define	_MAX_DIR	256

/**********************************************************************/
/* indicatos for old or new TM                                        */
/**********************************************************************/
#define OLD_TM      0
#define NEW_TM      1

/**********************************************************************/
/* indicator for organize                                             */
/* TM_CONVERT    - convert an ols TM to an new one                    */
/* TM_ORGANIZE   - organize a new TM                                  */
/**********************************************************************/
#define TM_CONVERT   0
#define TM_ORGANIZE  1


/**********************************************************************/
/* default threshold value for get                                    */
// GQ: beginning with TP6.0.1 the real fuzziness of a proposal (including
//     inline tagging is used. A new threshold has been added to be checked
//     against the new computed fuzziness, the old value is used
//     for the triple threshold checking
/**********************************************************************/
#define TM_DEFAULT_THRESHOLD     33   // prior: 40
#define TM_FUZZINESS_THRESHOLD   10

/**********************************************************************/
/* Marker for NTM in new TM properties                                */
/**********************************************************************/
#define NTM_MARKER "#@@NTM01@@#"

#include "win_types.h"

typedef LHANDLE HTM;
typedef CHAR  SHORT_FN  [FN_LENGTH];
typedef CHAR  BUFFERIN  [DATA_IN_SIZE];
typedef UCHAR BUFFEROUT  [DATA_OUT_SIZE],
              ACHPRIMKEY [PRIM_KEY_LENGTH],
              SZSECKEY   [MAX_SEC_LENGTH + 1];

typedef CHAR  LANG_LINE  [MAX_LINE_LENGTH + 1];
typedef CHAR  LONG_FN    [MAX_LONGFILESPEC];

typedef BYTE ABGROUP [CODEPAGE_SIZE];
typedef ABGROUP * PABGROUP;

typedef struct _TM_ADDRSS { /* addr */
   USHORT usEntryInDir,      /* >= 0, entry# of the cluster in KeyDir  */
                             /* <= 4095                                */
          usBlockNumber,     /* >  0, indicates block number in TM     */
                             /* 0  used for chaining purposes as null  */
          usDispBlockPtr;    /* size(block header) <= BLOCK_SIZE       */
                             /* indicates location within a block      */
} TM_ADDRESS, * PTM_ADDRESS ;

typedef struct _SEGMENT { /* seg */
   UCHAR   achSegMarker[SEG_MARKER_LENGTH] ;
                              /* marker to beginning of segment        */
   USHORT  usLenSegment,      /* total length of segment               */
           usDispIndustry,    /* industry codes location in bufData    */
           usLenIndustry,     /* length of indus. codes list(BYTES)    */
           usDispSource,      /* source location relative to bufData   */
           usLenSource,       /* source length in bytes                */
           usDispTarget,      /* target location relative to bufData   */
           usLenTarget,       /* target length in bytes                */
           usDispReserved,    /* Reserved area  location in bufData    */
           usLenReserved,     /* length of reserved area               */
           usDispSecKey,      /* secondary key  location in bufData    */
           usLenSecKey,       /* length of secondary key               */
           usDispContext,     /* Context area  location in bufData     */
           usLenContext;      /* length of context area                */
   SHORT_FN szFileName;       /* name of source file (short name)      */
   LONG_FN  szLongName;       /* name of source file (long name or EOS)*/
   USHORT  usSegNumber;       /* segment number in file                */
   EQF_BOOL fLogicalDel,      /* set when logically deleted segment    */
           fAscii;            /*                                       */
   USHORT  usTranslationFlag; /* type of translation, 0 = human, 1 = machine, 2 = Global Memory */
   TIME_L  tStamp;            /* time taken from c function            */
   BUFFERIN bufData;          /* fields with variable lengths          */
} SEGMENT, * PSEGMENT;

typedef struct _OLDSEGMENT { /* seg */
   UCHAR   achSegMarker[SEG_MARKER_LENGTH] ;
                              /* marker to beginning of segment        */
   USHORT  usLenSegment,      /* total length of segment               */
           usDispIndustry,    /* industry codes location in bufData    */
           usLenIndustry,     /* length of indus. codes list(BYTES)    */
           usDispSource,      /* source location relative to bufData   */
           usLenSource,       /* source length in bytes                */
           usDispTarget,      /* target location relative to bufData   */
           usLenTarget,       /* target length in bytes                */
           usDispReserved,    /* Reserved area  location in bufData    */
           usLenReserved,     /* length of reserved area               */
           usDispSecKey,      /* secondary key  location in bufData    */
           usLenSecKey;       /* length of secondary key               */
   SHORT_FN szFileName;       /* name of source file (short name)      */
   USHORT  usSegNumber;       /* segment number in file                */
   EQF_BOOL fLogicalDel,      /* set when logically deleted segment    */
           fAscii;            /*                                       */
   USHORT  usTranslationFlag; /* type of translation, 0 = human, 1 = machine, 2 = Global Memory */
   TIME_L  tStamp;            /* time taken from c function            */
   BUFFERIN bufData;          /* fields with variable lengths          */
} OLDSEGMENT, * POLDSEGMENT;

typedef struct _MATCH { /* mtch */
   TM_ADDRESS  addr;        /* address of the matching segment         */
   USHORT  usTranslationFlag; /* type of translation, 0 = human, 1 = machine, 2 = Global Memory */
   USHORT   usNumExactBytes;/* no. of exact bytes in the               */
                            /*     input and matched sentence          */
   TIME_L   tStamp;         /* time stamp of segment                   */
   LONG     lSimLevel,      /* <= 100 indicates similar                */
                            /* >= 200 indicate exact                   */
                            /* >= 300 indicate exact+same ind code     */
                            /* >= 400 indicate exact+same filename     */
            lLengthTest,    /* value of lengths test                   */
            lInitMatchTest, /* value of initials test                  */
            lWordsTest;     /* value of words test                     */
                     /* last 3 values are meaningless for exact matches*/
   UCHAR     szTarget[MAX_TGT_LENGTH + 1]; /* The target               */
} MATCH , * PMATCH;

/*
    More details about the match ranking method.

    The similarity level has a crude primary ranking as follows:

    400 - 499: If there is an exact match and the filename is the same.

    300 - 399: If there is an exact match, the filename is not the same,
                  but there is at least one industry code in common to
                  database segment and input segment.

    200 - 299: If there is an exact match but no filename or industry code
                  in common.

    0 - 100:   Similar match but no exact match.

    Secondary ranking within the ranges above is as follows:

    In the 400 - 499 range, the actual value is determined by proximity
        of database sentence number (within the text file from which it was
        taken), to the ordinal number of the input sentence within the input
        file.
    In the 300 - 399 range, the actual value is determined by number of equal
        industry codes vs the total number of industry codes that appear in
        both sentences.
    In the 200 - 299 range, the actual value is determined by the proximity
        of dates of the two segments.

    In the case of similar match the value is that of the init test. (See
        explanation to lInitMatchThr below.)

    The exact formulae by which the secondary ranking is evaluated is
        described both in the LLD document and in code comments.
                                                                       */

typedef struct  _PREFIX_IN {
   USHORT  usLenIn,           /* total length of input buffer          */
           idCommand ;        /* command id, previously defined.       */
// } PREFIX_IN, * PPREFIX_IN, IN, * PIN;
} PREFIX_IN, * PPREFIX_IN, * PIN;

typedef struct  _PREFIX_OUT {
   USHORT  usLenOut;           /* total length of output buffer        */
   BOOL    fDiskFull,          /* for Add /Replace / Create when number*/
   fDBfull;                    /* of blocks is a cluster exceeds       */
                               /* 2**16 - 1. Filled by FormatMore      */
   USHORT  rcTmt;              /* returned by TMT function             */

//} PREFIX_OUT, * PPREFIX_OUT, OUT, * POUT;
} PREFIX_OUT, * PPREFIX_OUT, * POUT;

typedef struct  _UPDATE_IN {
   PREFIX_IN  prefin;          /* prefix of each command               */
   SEGMENT    segIn;           /* the rest of this type is a SEGMENT   */
} UPDATE_IN, * PUPDATE_IN;

typedef UPDATE_IN  ADD_IN,  DEL_IN,  REP_IN;
typedef PUPDATE_IN PADD_IN, PDEL_IN, PREP_IN;

typedef struct  _ADD_OUT {
   PREFIX_OUT  prefout;     /* prefix of Output buffer                 */
   TM_ADDRESS  addr;        /* address of added segment                */
} ADD_OUT, * PADD_OUT;

typedef struct  _DEL_OUT {
   PREFIX_OUT  prefout;     /* prefix of Output buffer                 */
   TM_ADDRESS  addr;        /* address of deleted segment              */
} DEL_OUT , * PDEL_OUT ;

typedef struct  _REP_OUT {
   PREFIX_OUT  prefout;     /* prefix of Output buffer                 */
   SERVERNAME   szServer;   /* server name                             */
   TM_ADDRESS  addrDel,     /* address to delete                       */
               addrAdd;     /* address to add                          */
} REP_OUT , * PREP_OUT;

typedef struct  _CLOSE_IN  {
   PREFIX_IN  prefin ;      /* prefix of each command                  */
} CLOSE_IN, * PCLOSE_IN;

typedef struct  _CLOSE_OUT {
   PREFIX_OUT  prefout;     /* prefix of Output buffer                 */
} CLOSE_OUT, * PCLOSE_OUT;

typedef struct  _EXT_IN {
   PREFIX_IN  prefin;       /* prefix of each command                  */
   TM_ADDRESS addr;         /* address of extracted segment            */
   USHORT     usConvert;    // Indicates how the output should be converted
} EXT_IN  , * PEXT_IN ;

typedef struct  _EXT_OUT {
   PREFIX_OUT  prefout;     /* prefix of Output buffer                 */
   SERVERNAME   szServer;   /* server name                             */
   TM_ADDRESS  addr,        /* address of current segment              */
               addrNext;    /* address of next segment                 */
   SEGMENT     segOut;      /* fields with variable lengths            */
} EXT_OUT , * PEXT_OUT;

typedef struct _GET_IN {
   PREFIX_IN prefin;        /* prefix of each command                  */
   SHORT_FN  szFileName;    /* name of source file (short name)        */
   LONG_FN   szLongName;    /* name of source file (long name or EOS)  */
   USHORT    usConvert;    // Indicates how the output should be converted
   USHORT    usSegNumber,   /*                                         */
             usNumMatchesReq,/* number of matches required             */
             usDispIndustry,/* industry codes location in bufData      */
             usLenIndustry, /* length of indus. codes list(BYTES)      */
             usDispSource,  /* source location relative to bufData     */
             usLenSource;   /* source length in bytes                  */
   LONG      lLengthThr,    /* needed to filter out sentences          */
                            /* with different lengths                  */
             lInitMatchThr, /* needed to filter out sentences          */
                            /* with non matching initials              */
             lWordsMatchThr;/* needed to filter out sentences          */
                            /* with non matching words                 */
   BOOL      fAscii;        /*                                         */
   BUFFERIN  bufData;       /* fields with variable lengths            */
} GET_IN, * PGET_IN;

/**********************************************************************/
/* structure passed in case of rename a file ...                      */
/**********************************************************************/
typedef struct _RENFILE_IN
{
   PREFIX_IN    prefin;                /* prefix of each command             */
   SERVERNAME  szServer;                // server name
   CHAR    szOldFile[ MAX_EQF_PATH ];   // old file name
   CHAR    szNewFile[ MAX_EQF_PATH ];   // new file name
   CHAR         szUserId [MAX_USERID];  // userId logged on to requester
} RENFILE_IN, * PRENFILE_IN;

typedef struct _RENFILE_OUT
{
   PREFIX_OUT   prefout;                           /* prefix of each command */
} RENFILE_OUT, * PRENFILE_OUT;

/*  More details about lLengthThr and lInitMatchThr:

    lLengthThr:

    In the length test we compute a length value which measures how close
    are the lengths of the current sentence taken from the database versus
    the input sentence.
    The length value is computed by the formula:

    lLengthValue = ( EXTENT_SIMILAR * min( usLenInput, usLenCurrent ) ) /
                     max( usLenInput, usLenCurrent );

    where EXTENT_SIMILAR is the constant 100 for our purposes.

    The length is measured in number of words rather than characters.
    If LengthValue is 100 it means that both sentences have the same number of
    words. If one sentence has 10 words while the other has 5,
    lLengthValue = 100 * 5/10 which is about 50. In general LengthValue will
    be about the difference in percents. (10 and 5 differ by 50%).

    lLengthThr (the Length Threshold value) is the minimum value allowed in
    the length test. If LengthValue <= lLengthThr the length test fails.
    lLengthThread is increased in dependeny of the number of words of the
    input segment. For more detais see function LengthCorrectThresholds and
    CheckSimilar in file EQFTMRTV.C


    lMatchInitThr:

    lMatchInitThr is used to check whether the initials of words in both
    sentences is about the same. To that end we compute the value:

      lMatchValue = (EXTENT_SIMILAR * usSameInitilas) /
                                           max(usLenInput, usLenCurrent);

    where usSameInitials denotes the number of initials that are common
    to both sentences. lMatchValue is 100 if all the initials of one
    sentence are contained in the other.

    Assuming that both sentences have about the same number of words
    (since they passed the length test), the MatchValue denotes
    their similarity of initials in precents. If they have 20 words each
    and 15 initials are the same then MatchValue = 75.

    InitMatchThr is the minimal value allowed.
    An lActMatchThr is increased in dependency of the number of words in the
    input segment. For more detais see function LengthCorrectThresholds and
    CheckSimilar in file EQFTMRTV.C

    if MatchValue <= lActMatchThr the match value test fails

 */

typedef struct  _GET_OUT {
   PREFIX_OUT  prefout;     /* prefix of Output buffer                 */

   USHORT usNumMatchesFound,/* number of matches found                 */
          usNumMatchesValid,/* number of matches valid                 */
          ausSortedMatches[MAX_MATCH_TAB_ENTRIES];
   MATCH  amtchBest[MAX_MATCH_TAB_ENTRIES]; /* Matches array           */
} GET_OUT, * PGET_OUT;

typedef struct  _OPEN_IN {
   PREFIX_IN  prefin;       /* prefix of each command                  */
   SERVERNAME szServer;     /* servername                              */
   CHAR       szUserId [MAX_USERID]; /* userId logged on to requester  */
   FILENAME  szTmFileName;  /* name of Tm database to open             */
   BOOL       fExclusive;   /* indicate the mode for opening the file  */
   BOOL       fOpenGetPart; /* indicate if Open was due to a get part  */
} OPEN_IN , * POPEN_IN;


typedef struct  _OPEN_OUT {
   PREFIX_OUT  prefout;     /* prefix of Output buffer                 */
   HTM         htm;         /* handle to the TM                        */
} OPEN_OUT , * POPEN_OUT;

typedef struct _BLOCK_HEADER { /* bh */
   USHORT usBlockNum,       /* >= 1, points to previous block          */
          usPrevBlock,      /* >= 1, points to previous block          */
          usNextBlock,      /* >  1, points to next block.             */
                            /* 0 indicates no chaining                 */
          usFirstAvailByte; /* >= size of block header,                */
                            /* <= block size                           */
                            /* points to first available byte in block */
                            /* If block is full it sets to BlockSize   */
} BLOCK_HEADER , * PBLOCK_HEADER;

typedef struct _CREATE_TMH { /* ctmh */
   FILENAME  szTmFileName;  /* Tm database name                        */
   USHORT    usBlockSize;
   LANGUAGE  szSourceLang,  /* source language                         */
             szTargetLang;  /* target language                         */
   EQF_BOOL  fDbcs;         /* double byte char support 0/1            */
} CREATE_TMH;

typedef struct _CREATE_IN { /* crei */
   PREFIX_IN  prefin;       /* prefix of each command                  */
   SERVERNAME szServer;
   CREATE_TMH ctmh;         /* parameters that copied into Tm header   */
   TIME_L  tCreate;         /* creation time stamp                     */
   ABGROUP abABGrouping;
   USHORT  usDispExclTagList, /* offset of tag list                    */
           usLenExclTagList,  /* length of tag list                    */
           usDispExclWordList,/* offset of word list                   */
           usLenExclWordList; /* length of word list                   */
   CHAR    bufData[CREATE_BUFFER_SIZE];
   CHAR    szUserId [MAX_USERID]; /* userId logged on to requester     */
} CREATE_IN , * PCREATE_IN;

typedef OPEN_OUT CREATE_OUT, *PCREATE_OUT;

typedef CLOSE_IN   INFO_IN, * PINFO_IN;

typedef struct _INFO_OUT  { /* infi */
   PREFIX_OUT prefout;      /* prefix of each command                  */
   CREATE_TMH ctmh;         /* parameters that copied into Tm header   */
   TIME_L  tCreate;         /* creation time stamp                     */
   ABGROUP abABGrouping;
   USHORT  usDispExclTagList, /* offset of tag list                    */
           usLenExclTagList,  /* length of tag list                    */
           usDispExclWordList,/* offset of word list                   */
           usLenExclWordList; /* length of word list                   */
   CHAR    bufData[CREATE_BUFFER_SIZE];
} INFO_OUT , * PINFO_OUT;

// ----------------------------------------------------------------------------
// structures needed for the TMC_GET_SERVER_DRIVES command which lists all
// disk drives on a server (which are available for the EQF TM Server program)
// The first Drive returned is the system drive (where directory \COMMPROP
// is located - this directory can only exist on the system drive, not on
// any of the secondary drives)
// ----------------------------------------------------------------------------

typedef struct _DRIVES_IN {              /* indr */
   PREFIX_IN    prefin;                  /* prefix of each command */
   SERVERNAME   szServer;                /* which server ?         */
   CHAR         szUserId [MAX_USERID];   /* userId logged on to requester */
} DRIVES_IN, * PDRIVES_IN;

typedef struct _DRIVE_INFO {      /* drin */
   CHAR         cDriveLetter;     /* drive letter of disk drive              */
   ULONG        ulFreeSpace;      /* number of bytes left on this disk drive */
} DRIVE_INFO, * PDRIVE_INFO;

typedef struct _DRIVES_OUT {                    /* outdr */
   PREFIX_OUT   prefout;                        /* prefix of each command    */
   USHORT       usValidDrives;                  /* how much drives have been */
                                                /* found on the server ?     */
   DRIVE_INFO   adrinDrives [MAX_DRIVELIST];    /* info for each valid       */
                                                /* server drive              */
} DRIVES_OUT, * PDRIVES_OUT;


// ----------------------------------------------------------------------------
// structures needed for the TMC_GET_SERVER_TM_LIST command which lists all
// translation memories that have been found on the selected server; for each
// TM its full path name and its current file size is returned
// ----------------------------------------------------------------------------
typedef struct _FILE_LIST_IN {         /* intl                          !!! CHM */
   PREFIX_IN    prefin;                /* prefix of each command        */
   SERVERNAME   szServer;              /* which server ?                */
   CHAR         szUserId [MAX_USERID]; /* userId logged on to requester */
} FILE_LIST_IN, * PFILE_LIST_IN; // !!! CHM

typedef struct _FILE_INFO {                      /* tmin !!! CHM */
   CHAR         szPathFileName [MAX_EQF_PATH];   /* full filename of file    */
   ULONG        ulFileSize;                      /* filesize in bytes        */
} FILE_INFO, * PFILE_INFO; // !!! CHM


typedef struct _FILE_LIST_OUT {                    /* outtl !!! CHM */
   PREFIX_OUT   prefout;                           /* prefix of each command */
   USHORT       usValidFiles;                      /* valid entries in array */
   FILE_INFO    aflinFileList [MAX_TM_LIST_NUMBER]; /* info for avail. files */
} FILE_LIST_OUT, * PFILE_LIST_OUT; // !!! CHM


// ----------------------------------------------------------------------------
// structures needed for the TMC_GET_PART_OF_TM_FILE command that transfers
// a selected part of the physical TM file to the Troja requester; input
// structure contains file offset and number of bytes to transfer within this
// block; the returned value of bytes read indicates whether the end of file
// has been reached (ulBytesRead < ulBytesToRead OR ulBytesRead = 0); the
// maximum size to transfer at a time is GETPART_BUFFER_SIZE
// ----------------------------------------------------------------------------


typedef struct _GETPART_IN {      /* ingp */
   PREFIX_IN    prefin;           /* prefix of each command                  */
   ULONG        ulFilePos;        /* file position of first byte to transfer */
   ULONG        ulBytesToRead;    /* number of bytes to transfer             */
} GETPART_IN, * PGETPART_IN;

typedef struct _GETPART_OUT {          /* outgp */
   PREFIX_OUT   prefout;               /* prefix of each command             */
   ULONG        ulBytesRead;           /* number of bytes actually read      */
   ULONG        ulNextFilePos;         /* file position of next byte to read */
   UCHAR        aucOutBuffer [GETPART_BUFFER_SIZE]; /* output buffer        */
} GETPART_OUT, * PGETPART_OUT;

typedef struct _GETDICTPART_IN {
   PREFIX_IN    prefin;           /* prefix of each command                  */
   SERVERNAME   szServer;         /* which server ?                          */
   PVOID        pBTree ;          // ptr to dict file handles
   ULONG        ulFilePos;        /* file position of first byte to transfer */
   ULONG        ulBytesToRead;    /* number of bytes to transfer             */
} GETDICTPART_IN, * PGETDICTPART_IN;

// ----------------------------------------------------------------------------
// structures needed for the TMC_PUT_TM_PROPERTIES command which is used to
// copy a property file for a remote TM to the server (during TM creation
// process); the contents of the property file are read into the input buffer
// which is up to MEM_PROP_SIZE bytes long; the actual length of the
// property file has to be passed in the ulPropLength field; the field
// szTMPathFileName contains the name of the TM file on the server (including
// the drive and path) which is then used to create a filename for the property
// file (same drive and path but new extension (will be .PRP)
// ----------------------------------------------------------------------------
typedef struct _PUTPROP_IN {                   /* inpp                          */
   PREFIX_IN    prefin;                        /* prefix of each command        */
   SERVERNAME   szServer;                      /* which server ?                */
   CHAR         szPathFileName [MAX_EQF_PATH]; /* full filename                 */
   ULONG        ulPropLength;                  /* length of property file       */
   UCHAR        aucInBuffer [MEM_PROP_SIZE];   /* buffer for file data          */
   CHAR         szUserId [MAX_USERID];         /* userId logged on to requester */
} PUTPROP_IN, * PPUTPROP_IN;

// !!! CHM Start
typedef struct _PUTDICTPROP_IN {               /* inpp                          */
   PREFIX_IN    prefin;                        /* prefix of each command        */
   SERVERNAME   szServer;                      /* which server ?                */
   CHAR         szPathFileName [MAX_EQF_PATH]; /* full filename                 */
   ULONG        ulPropLength;                  /* length of property file       */
   CHAR         szUserId [MAX_USERID];         /* userId logged on to requester */
   PROPDICTIONARY DictProp;                    /* dictionary property buffer    */
} PUTDICTPROP_IN, * PPUTDICTPROP_IN;

/* define union to allow combined processing in server code */
typedef union _PUTPROPCOMBINEDIN
{
   PUTPROP_IN     TmPropIn;
   PUTDICTPROP_IN DictPropIn;
} PUTPROPCOMBINED_IN, * PPUTPROPCOMBINED_IN;
// !!! CHM End

typedef struct _PUTPROP_OUT {                      /* outpp                     */
   PREFIX_OUT   prefout;                           /* prefix of each command    */
} PUTPROP_OUT, * PPUTPROP_OUT;


// ----------------------------------------------------------------------------
// structures needed for the TMC_GET_TM_PROPERTIES command which is used to
// copy a property file for a remote TM from the server to the Troja requester
// (during 'Include Remote TM' process); the contents of the property file are
// put into the output buffer which is up to MEM_PROP_SIZE bytes long; the
// actual length of the property file will be passed in the ulPropLength field;
// the field szTMPathFileName must contain the full path name of the TM file
// on the server and will be used to create the filename of the belonging
// property file which is stored on the same disk in the same path with the
// extension .PRP
// ----------------------------------------------------------------------------
typedef struct _GETPROP_IN {                   /* ingp                          */
   PREFIX_IN    prefin;                        /* prefix of each command        */
   SERVERNAME   szServer;                      /* which server ?                */
   CHAR         szPathFileName [MAX_EQF_PATH]; /* full filename                 */
   CHAR         szUserId [MAX_USERID];         /* userId logged on to requester */
} GETPROP_IN, * PGETPROP_IN;

typedef struct _GETPROP_OUT {                     /* outgp                     */
   PREFIX_OUT   prefout;                          /* prefix of each command    */
   ULONG        ulPropLength;                     /* length of property file   */
   UCHAR        aucOutBuffer [MEM_PROP_SIZE];     /* buffer for file data      */
} GETPROP_OUT, * PGETPROP_OUT;

// !!! CHM Start
typedef struct _GETDICTPROP_OUT {                 /* outgp                     */
   PREFIX_OUT   prefout;                          /* prefix of each command    */
   ULONG        ulPropLength;                     /* length of property file   */
   PROPDICTIONARY DictProp;                       /* dictionary property buffer*/
} GETDICTPROP_OUT, * PGETDICTPROP_OUT;

/* define union to allow combined processing in server code */
typedef union _GETPROPCOMBINEDOUT
{
   GETPROP_OUT       TmPropOut;
   GETDICTPROP_OUT   DictPropOut;
} GETPROPCOMBINED_OUT, * PGETPROPCOMBINED_OUT;
// !!! CHM End


// ----------------------------------------------------------------------------
// structures needed for the TMC_END_ORGANIZE command which is used to end a
// running 'Organize' process; this command is sent to the original TM instead
// of the TM_CLOSE command and handles the closing, deletion and renaming of
// the original and temporary TM file; the temporary file has to be closed
// previously; the two filenames must contain the full specifications of the
// original TM file to be deleted and the temporary file to be renamed to the
// original TM filename;
// ----------------------------------------------------------------------------
typedef struct _ENDORG_IN {            /* ineo */
   PREFIX_IN    prefin;                /* prefix of each command             */
   CHAR         szOrgTM [MAX_EQF_PATH];/* full filename of original TM file  */
   CHAR         szTmpTM [MAX_EQF_PATH];/* full filename of temporary TM file */
} ENDORG_IN, * PENDORG_IN;

typedef struct _ENDORG_OUT {                       /* outeo */
   PREFIX_OUT   prefout;                           /* prefix of each command */
} ENDORG_OUT, * PENDORG_OUT;


// ----------------------------------------------------------------------------
// structures needed for the TMC_DELETE_TM command which is used to physical
// delete a TM file and the belonging property file on the server;
// before this command can be submitted, the file has to opened exclusively;
// the supplied filename must contain the full drive and path information;
// ----------------------------------------------------------------------------
typedef struct _DELTM_IN {                       /* indt */
   PREFIX_IN    prefin;                          /* prefix of each command   */
   CHAR         szTMPathFileName [MAX_EQF_PATH]; /* full filename of TM file */
   CHAR         szPropPathFileName[MAX_EQF_PATH]; /* full filename of Prop file */
} DELTM_IN, * PDELTM_IN;

typedef struct _DELTM_OUT {                        /* outdt */
   PREFIX_OUT   prefout;                           /* prefix of each command */
} DELTM_OUT, * PDELTM_OUT;


// ----------------------------------------------------------------------------
// structures needed for the TMC_DELETE_FILE command which is used to physical
// delete a file on the server; this command is only used during startup of the
// TM organization process to cleanup eventually existing temporary files (from
// a previous organize process that died during execution);
// the supplied filename must contain the full drive and path information;
// ----------------------------------------------------------------------------
typedef struct _DELFILE_IN {               /* indf                           */
   PREFIX_IN    prefin;                    /* prefix of each command         */
   SERVERNAME   szServer;                  /* which server ?                 */
   CHAR         szFileName [MAX_EQF_PATH]; /* full filename of file to delete*/
   CHAR         szUserId [MAX_USERID];     /* userId logged on to requester  */
} DELFILE_IN, * PDELFILE_IN;

typedef struct _DELFILE_OUT {                      /* outdf                  */
   PREFIX_OUT   prefout;                           /* prefix of each command */
} DELFILE_OUT, * PDELFILE_OUT;

typedef struct  _CLOSEHANDLER_IN
{
   PREFIX_IN   prefin;
   USHORT      hth;
} CLOSEHANDLER_IN, * PCLOSEHANDLER_IN;

typedef struct  _EXIT_IN
{
   PREFIX_IN   prefin;
} EXIT_IN, * PEXIT_IN;

typedef struct  _EXIT_OUT
{
   PREFIX_OUT  prefout;
} EXIT_OUT, * PEXIT_OUT;

// ----------------------------------------------------------------------------
// data structure used for the TMC_QUERY_FILE_INFO which returns the file info
// structure of the specified file returned by the DosFindFirst call on the
// server
// ----------------------------------------------------------------------------

typedef struct _FILEINFO_IN {                      /* infi */
   PREFIX_IN    prefin;                            /* prefix of each command */
   CHAR         szFileName [MAX_EQF_PATH]; /* full filename of file to query */
   SERVERNAME   szServer;                          /* which server ?         */
   CHAR         szUserId [MAX_USERID]; /* userId logged on to requester !!!! CHM */
} FILEINFO_IN, * PFILEINFO_IN;

typedef struct _FILEINFO_OUT {                  /* outfi */
   PREFIX_OUT   prefout;                        /* prefix of each command    */
   FILEFINDBUF  stFile;                         /* info about file           */
} FILEINFO_OUT, * PFILEINFO_OUT;


typedef struct _TM_HEADER { /* tmh */
/* fixed part */
   UCHAR    achTmPrefix[TM_PREFIX_SIZE];
                            /* should be initiated to EQFTMT$$ 8       */
   USHORT  usTmHeaderSize,  /* actual length of tm header              */
           usDbVersion;
   LONG    ldispFirstBlock; /* disp of first block from                */
                            /* beginning of TM                         */
   CREATE_TMH ctmh;         /* parameters provided by the create       */
   TIME_L  tCreate;         /* creation time stamp                     */
   ABGROUP abABGrouping;

/* updated part */
   EQF_BOOL    fCorruption;
   USHORT  usNumTMBlocks,    /* number of blocks in the TM             */
           usNumFreeBlocks,  /* # of free, pre-formatted blocks        */
           usFirstAvailBlock,/* points to first available block        */
           ausKeyDirectory[KEY_DIR_SIZE],   /* key directory           */

           usDispExclTagList, /* offset of tag list                    */
           usLenExclTagList,  /* length of tag list                    */
           usDispExclWordList,/* offset of word list                   */
           usLenExclWordList; /* length of word list                   */

} TM_HEADER, * PTM_HEADER, ** PPTM_HEADER;

#define TAG_LEN             35
#define MAX_NAME            8
#define MAX_RANDOM          20
//#define MAX_VOTES           20 //     30
#define MAX_VOTES           30           // change 27.2.2000
#define ABS_VOTES           400
#define MAX_MATCHES         15
#define TOK_SIZE            4000
#define MAX_COMPACT_SIZE    3217   // 256
#define TMX_REC_SIZE        32760
#define TMX_TABLE_SIZE      512
#define MAX_INDEX_LEN       8150 //  2048

/**********************************************************************/
/* The version number is stored in the signature record of the TMs    */
/*                                                                    */
/* TM_MAJ_VERSION and TM_MIN_VERSION is always the current version    */
/* used to create new TMs                                             */
/*                                                                    */
/* A change of the major version always forces an organize of the     */
/* TM. If the major version of a TM is larger than the TM_MAJ_VERSION */
/* used during compile of the DLLs the TM cannot be opened (even not  */
/* for organize). A message will be displayed which will tell the     */
/* user to get a new version of TranslationManager to work with the   */
/* TM.                                                                */
/*                                                                    */
/* Version | Description                 | Special Handling for TMs   */
/* Maj Min |                             |                            */
/* --------+-----------------------------+----------------------------*/
/*  1   0  | Base version of TMs         | use old hash and tokenize  */
/*         |                             | functions                  */
/* --------+-----------------------------+----------------------------*/
/*  2   0  | This version uses new hash  |                            */
/*         | and tokenize functions to   |                            */
/*         | overcome the problems with  |                            */
/*         | non-alphabetic characters in|                            */
/*         | terms and not-recognized    |                            */
/*         | attribute strings           |                            */
/* --------+-----------------------------+----------------------------*/
/*  3   0  | - This version number is set|                            */
/*         |   automatically when a      |                            */
/*         |   version 2 TM has tersed   |                            */
/*         |   name tables (because the  |                            */
/*         |   table exceeds the 32k QDAM|                            */
/*         |   barrier for data records) |                            */
/*         | - the version number has    |                            */
/*         |   been splitted into a byte |                            */
/*         |   for the major version and |                            */
/*         |   a byte for the minor      |                            */
/*         |   version                   |                            */
/* --------+-----------------------------+----------------------------*/
/*  4   0  | - removed multiple flag     |                            */
/*         | - use protect table exit    |                            */
/*         |   for tag recognition       |                            */
/*         | - use least-edit string     |                            */
/*         |   for fuzzy match ranking   |                            */
/* --------+-----------------------------+----------------------------*/
/*  5   0  | - allow name tables with    |                            */
/*         |   a size of more than 32kB  |                            */
/*         |   (organize of TM required) |                            */
/* --------+-----------------------------+----------------------------*/
/*  6   0  | - allow text in unicode     |                            */
/*         |   a size of more than 32kB  |                            */
/*         |   (organize of TM required) |                            */
/* --------+-----------------------------+----------------------------*/
/*  7   0  | - OpenTM2 Memory Plugin     |                            */
/*         |   driven memory             |                            */
/* --------+-----------------------------+----------------------------*/
/*  7   1  | - New HashTupel method for  |                            */
/*         |   the handling of words with|                            */
/*         |   more than 20 characters   |                            */
/*         |   (organize of TM required  |                            */
/*         |   to activate new method,   |                            */
/*         |   w/o organize old method is|                            */
/*         |   being used)               |                            */
/* --------+-----------------------------+----------------------------*/
/* Current version: 7.0                                               */
/**********************************************************************/
#define TM_VERSION_1        1
#define TM_VERSION_2        2
#define TM_MAJ_VERSION_2    2
#define TM_MAJ_VERSION_3    3
#define TM_MAJ_VERSION_4    4
#define TM_MAJ_VERSION_5    5
#define TM_MAJ_VERSION_6    6
#define TM_MAJ_VERSION_7    7

#define TMMIN_VERSION_0     0
#define TMMIN_VERSION_1     1

#define TM_MAJ_VERSION      8
#define TM_MIN_VERSION      1


//#ifdef TM_LARGENAMETABLES
//  #define TM_MAJ_VERSION      5
//  #define TM_MIN_VERSION      0
//#elif defined(TOP98_MULTFLAG)
//  #define TM_MAJ_VERSION      4
//  #define TM_MIN_VERSION      0
//#else
//  #define TM_MAJ_VERSION      2
//  #define TM_MIN_VERSION      0
//#endif

//signature structure

#define _TMX_SIGN_SZ_NAME 128
//#define _TMX_SIGN_SZ_NAME MAX_FILESPEC

typedef struct _TMX_SIGN
{
  TIME_L lTime;  
  BYTE bMajorVersion;
  BYTE bMinorVersion;
  CHAR szName[_TMX_SIGN_SZ_NAME];
  CHAR szSourceLanguage[MAX_LANG_LENGTH];
  CHAR szDescription[MAX_MEM_DESCRIPTION];

} TMX_SIGN, * PTMX_SIGN;

//table entry structure
typedef struct _TMX_TABLE_ENTRY
{
  CHAR   szName[MAX_LANG_LENGTH];
  USHORT usId;
} TMX_TABLE_ENTRY, * PTMX_TABLE_ENTRY;

  // name table structure (TM Version 1 - 4)
  typedef struct _TMX_VER1_TABLE
  {
    USHORT usAllocSize;
    USHORT usMaxEntries;
    TMX_TABLE_ENTRY stTmTableEntry;
  } TMX_VER1_TABLE, * PTMX_VER1_TABLE;

  // name table structure (TM version 5 and up)
  typedef struct _TMX_TABLE
  {
    ULONG  ulAllocSize;
    ULONG  ulMaxEntries;
    TMX_TABLE_ENTRY stTmTableEntry;
  } TMX_TABLE, * PTMX_TABLE;

/**********************************************************************/
/* Defines and structures for the long document name support          */
/**********************************************************************/

// initial size of long name buffer area
#define LONGNAMEBUFFER_SIZE 8096

// initial number of entries in long document name pointer array
// and increment for table enlargements
#define LONGNAMETABLE_ENTRIES 32

// table entry structure for long document name table
typedef struct _TMX_LONGNAME_TABLE_ENTRY
{
  PSZ    pszLongName;                  // ptr to long name in buffer area
  USHORT usId;                         // ID for long name
} TMX_LONGNAME_TABLE_ENTRY, * PTMX_LONGNAME_TABLE_ENTRY;

//table structure for long document table
typedef struct _TMX_LONGNAME_TABLE
{
  PSZ    pszBuffer;                              // buffer for names and IDs
  ULONG  ulBufUsed;                              // number of bytes used in buffer
  ULONG  ulBufSize;                              // size of buffer in bytes
  ULONG  ulTableSize;                            // table size (# entries)
  ULONG  ulEntries;                              // number of entries in table
  TMX_LONGNAME_TABLE_ENTRY stTableEntry[1];      // dyn. array of table entries
} TMX_LONGNAMETABLE, * PTMX_LONGNAME_TABLE;


// Values for update counter indices
#define RESERVED_UPD_COUNTER     0
#define COMPACTAREA_UPD_COUNTER  1
#define AUTHORS_UPD_COUNTER      2
#define FILENAMES_UPD_COUNTER    3
#define LANGUAGES_UPD_COUNTER    4
#define TAGTABLES_UPD_COUNTER    5
#define LONGNAMES_UPD_COUNTER    6
#define MAX_UPD_COUNTERS        20


//TM control block structure
typedef struct _TMX_CLB
{
  PVOID pstTmBtree;
  PVOID pstInBtree;
  PTMX_TABLE pLanguages;
  PTMX_TABLE pFileNames;
  PTMX_TABLE pAuthors;
  PTMX_TABLE pTagTables;
  USHORT usAccessMode;
  USHORT usThreshold;
  TMX_SIGN stTmSign;
  BYTE     bCompact[MAX_COMPACT_SIZE-1];
  BYTE     bCompactChanged;
  LONG     alUpdCounter[MAX_UPD_COUNTERS];
  //BOOL     fShared;
  PTMX_LONGNAME_TABLE pLongNames;
  PTMX_TABLE pLangGroups;              //  table containing language group names
  PSHORT     psLangIdToGroupTable;     // language ID to group ID table
  LONG       lLangIdToGroupTableSize; // size of table (alloc size)
  LONG       lLangIdToGroupTableUsed; // size of table (bytes in use)
  PVOID      pTagTable;               // tag table loaded for segment markup (TBLOADEDTABLE)

  // copy of long name table sorted ignoring the case of the file names
  // Note: only the stTableEntry array is filled in this area, for all other
  //       information use the entries in the pLongNames structure
  PTMX_LONGNAME_TABLE pLongNamesCaseIgnore;

  // fields for work area pointers of various subfunctions which are allocated
  // only once for performance reasons
  PVOID      pvTempMatchList;        // matchlist of FillMatchEntry function
  PVOID      pvIndexRecord;          // index record area of FillMatchEntry function
  PVOID      pvTmRecord;             // buffer for memory record used by GetFuzzy and GetExact
  ULONG      ulRecBufSize;           // current size of pvTMRecord;
  PVOID      pvNotUsed[10];          // room for additional pointers and size values

  // fields for time measurements and logging
  BOOL       fTimeLogging;           // TRUE = Time logging is active
  LONG64     lAllocTime;             // time for memory allocation
  LONG64     lTokenizeTime;          // time for tokenization
  LONG64     lGetExactTime;          // time for GetExact
  LONG64     lOtherTime;             // time for other activities
  LONG64     lGetFuzzyTime;          // time for GetFuzzy
  LONG64     lFuzzyOtherTime;        // other time spent in GetFuzzy
  LONG64     lFuzzyTestTime;         // FuzzyTest time spent in GetFuzzy
  LONG64     lFuzzyGetTime;          // NTMGet time spent in GetFuzzy
  LONG64     lFuzzyFillMatchEntry;   // FillMatchEntry time spent in GetFuzzy
  LONG64     lFillMatchAllocTime;    // FillMatchEntry: allocation time
  LONG64     lFillMatchOtherTime;    // FillMatchEntry: other times
  LONG64     lFillMatchReadTime;     // FillMatchEntry: read index DB time
  LONG64     lFillMatchFillTime;     // FillMatchEntry: fill match list time
  LONG64     lFillMatchCleanupTime;  // FillMatchEntry: cleanup match list time
  LONG64     lFillMatchFill1Time;     // FillMatchEntry: fill match list time
  LONG64     lFillMatchFill2Time;     // FillMatchEntry: fill match list time
  LONG64     lFillMatchFill3Time;     // FillMatchEntry: fill match list time
  LONG64     lFillMatchFill4Time;     // FillMatchEntry: fill match list time
  LONG64     lNotUsed[7];           // room for more counters
} TMX_CLB, * PTMX_CLB;

//complete entry id tm data file
typedef struct _TMX_RECORD
{
  LONG   lRecordLen;
  USHORT  usSourceRecord;
  USHORT  usFirstTargetRecord;
} TMX_RECORD, * PTMX_RECORD;

typedef struct _TMX_OLD_RECORD
{
  USHORT  usRecordLen;
  USHORT  usSourceRecord;
  USHORT  usFirstTargetRecord;
} TMX_OLD_RECORD, * PTMX_OLD_RECORD;

//structure of the source segment
typedef struct _TMX_SOURCE_RECORD
{
  LONG   lRecordLen;
  USHORT  usSource;
  USHORT usLangId;
} TMX_SOURCE_RECORD, * PTMX_SOURCE_RECORD;

//structure of the target segment
typedef struct _TMX_TARGET_RECORD
{
  LONG   lRecordLen;
  USHORT  usSourceTagTable;
  USHORT  usTargetTagTable;
  USHORT  usTarget;
  USHORT  usClb;
} TMX_TARGET_RECORD, * PTMX_TARGET_RECORD;


//control block structure in target record
typedef struct _TMX_TARGET_CLB
{
  BYTE    bMultiple;
  USHORT  usSrcLangId;
  USHORT  usLangId;
  BYTE    bTranslationFlag;
  TIME_L  lTime;
  USHORT  usFileId;
  ULONG   ulSegmId;   // changed from USHORT
  USHORT  usAuthorId;
  USHORT  usAddDataLen;  // new for Major_version6: Length of following context and additional info data
} TMX_TARGET_CLB, * PTMX_TARGET_CLB;

// helper macros for working with TMX_TARGET_CLBs
#define TARGETCLBLEN( pClb ) (sizeof(TMX_TARGET_CLB) + pClb->usAddDataLen)

#define NEXTTARGETCLB( pClb ) ((PTMX_TARGET_CLB)(((PBYTE)pClb) + TARGETCLBLEN(pClb)))

#define PCONTEXTFROMCLB( pClb ) ((PSZ_W)(((PBYTE)pClb)+sizeof(TMX_TARGET_CLB)))

// max size of additional data area
// (currently 2 * MAX_SEGMENT_SIZE for context and additional info
// plus size of three identifierrs (USHORT) and two size fields (USHORT) )
#define MAX_ADD_DATA_LEN ((2 * MAX_SEGMENT_SIZE)*sizeof(WCHAR) + (5 * sizeof(USHORT)))

// identifier for additional info data in additional data area
#define ADDDATA_ADDINFO_ID 1

// identifier for context data in additional data area
#define ADDDATA_CONTEXT_ID 2

// identifier for the end of the additional data area
#define ADDDATA_ENDOFDATA_ID 9

// compute the size of the additional data for the given input
USHORT NTMComputeAddDataSize( PSZ_W pszContext, PSZ_W pszAddInfo );

// get length of specific data in the combined data area, returns length of data area
USHORT NtmGetAddDataLen( PTMX_TARGET_CLB pCLB, USHORT usDataID );

// store/combine additional data in the combined area, returns new size of combined data area or 0 in case of errors
USHORT NtmStoreAddData( PTMX_TARGET_CLB pCLB, USHORT usDataID, PSZ_W pszAddData );

// retrieve specific data from the combined data area, returns length of retrieved data (incl. string end delimiter)
USHORT NtmGetAddData( PTMX_TARGET_CLB pCLB, USHORT usDataID, PSZ_W pszBuffer, USHORT usBufSize );

// find a string in a specific data area
BOOL NtmFindInAddData( PTMX_TARGET_CLB pCLB, USHORT usDataID, PSZ_W pszSearch );

typedef struct _TMX_OLD_TARGET_CLB
{
  BYTE    bMultiple;
  USHORT  usLangId;
  BYTE    bMT;
  TIME_L  lTime;
  USHORT  usFileId;
  USHORT  usSegmId;
  USHORT  usAuthorId;
} TMX_OLD_TARGET_CLB, * PTMX_OLD_TARGET_CLB;


//tag table structure for both source and target
typedef struct _TMX_TAGTABLE_RECORD
{
  LONG   lRecordLen;
  USHORT  usTagTableId;
  USHORT  usFirstTagEntry;
} TMX_TAGTABLE_RECORD, * PTMX_TAGTABLE_RECORD;

typedef struct _TMX_OLD_TAGTABLE_RECORD
{
  USHORT  usRecordLen;
  USHORT  usTagTableId;
  USHORT  usFirstTagEntry;
} TMX_OLD_TAGTABLE_RECORD, * PTMX_OLD_TAGTABLE_RECORD;

//individual tag entry in tag table record
typedef struct _TMX_TAGENTRY
{
  USHORT  usOffset;
  USHORT  usTagLen;
  BYTE    bData;
} TMX_TAGENTRY, * PTMX_TAGENTRY;

// macros to access certain TM records fields
  #define RECLEN(pRec) pRec->lRecordLen


#define NTMVOTES(l)     ((BYTE)(((ULONG)(l) >> 24) & 0xFF))
#define NTMKEY(l)       ((ULONG)(l) & 0xFFFFFF)
#define NTMINDEX(b,l)   ((ULONG)(((l) & 0xFFFFFF) | (((ULONG)(b)) << 24 )))

typedef ULONG  TMX_INDEX_ENTRY, *PTMX_INDEX_ENTRY;

typedef struct _TMX_INDEX_RECORD
{
  USHORT  usRecordLen;
  TMX_INDEX_ENTRY  stIndexEntry;
} TMX_INDEX_RECORD, * PTMX_INDEX_RECORD;

typedef struct _TMX_TERM_TOKEN
{
   USHORT usOffset;
   USHORT usLength;
   USHORT usHash;
} TMX_TERM_TOKEN, *PTMX_TERM_TOKEN;

typedef struct _TMX_MATCHENTRY
{
  ULONG ulKey;
  USHORT usMaxVotes;
  USHORT usMatchVotes;
  BYTE cCount;
} TMX_MATCHENTRY, * PTMX_MATCHENTRY;

//#pragma pack(show)      
//#pragma pack(push, 8)
//#pragma pack(8)

typedef struct _TMX_SENTENCE
{
  PSZ_W pInputString;
  PSZ_W pNormString;
  //PSZ_W pInputStringWNormalizedTags;
  PSZ_W pNormStringStart;
  USHORT  usNormLen;
  PTMX_TERM_TOKEN pTermTokens;
  LONG lTermAlloc;
  PTMX_TAGTABLE_RECORD pTagRecord;
  LONG lTagAlloc;
  PTMX_TAGENTRY pTagEntryList;
  USHORT  usActVote;
  PULONG  pulVotes;
  PSZ_W pPropString;                   // proposal string (with tagging)
  PTMX_TERM_TOKEN pPropTermTokens;     // buffer for Termtokens
} TMX_SENTENCE, * PTMX_SENTENCE;


//#pragma pack(pop)
//#pragma pack()

typedef struct _TMX_SENTENCE_V5
{
  PSZ pInputString;
  PSZ pNormString;
  PSZ pNormStringStart;
  USHORT  usNormLen;
  PTMX_TERM_TOKEN pTermTokens;
  LONG lTermAlloc;
  PTMX_TAGTABLE_RECORD pTagRecord;
  LONG lTagAlloc;
  PTMX_TAGENTRY pTagEntryList;
  USHORT  usActVote;
  PULONG  pulVotes;
  PSZ_W pPropString;                   // proposal string (with tagging)
  PTMX_TERM_TOKEN pPropTermTokens;     // buffer for Termtokens
} TMX_SENTENCE_V5, * PTMX_SENTENCE_V5           ;


typedef struct _TMX_REPLTAGPAIR
{
  PBYTE     pSrcTok;           // token for paired toks
  PBYTE     pPropTok;
  BOOL      fUsed;             //TRUE = Tag pair has been used in replacement already
} TMX_REPLTAGPAIR, * PTMX_REPLTAGPAIR;

typedef struct _TMX_SUBSTPROP
{
  CHAR_W szSource    [ MAX_SEGMENT_SIZE ]; // source segment
  CHAR_W szPropSource[ MAX_SEGMENT_SIZE ]; // source proposal
  CHAR_W szPropTarget[ MAX_SEGMENT_SIZE ]; // translation of proposal
  char szSourceLanguage[MAX_LANG_LENGTH];// source language
  char szSourceTagTable[MAX_FNAME];      // source tagtable
  char szTargetLanguage[MAX_LANG_LENGTH];// target language
  char szPropTagTable[MAX_FNAME];        // tagtable for proposal
  PBYTE                pTokSource;       // token buffer for source tokens
  PBYTE                pTokPropSource;   // token buffer for proposal tokens
  PBYTE                pTokPropTarget;   // token buffer for proposal target ..
  PTMX_TAGTABLE_RECORD pTagsSource;      // tag table record for source  ..
  PTMX_TAGTABLE_RECORD pTagsPropSource;  // tag table record for prop source
  PTMX_TAGTABLE_RECORD pTagsPropTarget;  // tag table record for prop target
  CHAR_W chBuffer[ MAX_SEGMENT_SIZE * 2 ]; // generic token buffer
  USHORT usTokenSource;                  // number of source tokens
  USHORT usTokenPropSource;              // number of prop source tokens
  USHORT usTokenPropTarget;              // number of prop target tokens
  ULONG  ulRandom[MAX_RANDOM];                   // random sequence number
  PTMX_REPLTAGPAIR pTagPairs;                    // tags to be replaced by each other
  PTMX_REPLTAGPAIR pDelTagPairs;                 // tags to be deleted in prop
} TMX_SUBSTPROP, * PTMX_SUBSTPROP;



//=======================================================================
typedef struct _TMX_PREFIX_IN
{
  USHORT usLengthInput;                //length of complete input structure
  USHORT usTmCommand;                  //TM command id
} TMX_PREFIX_IN, * PTMX_PREFIX_IN, XIN, * PXIN;

//prefix for each output structures
typedef struct _TMX_PREFIX_OUT
{
  USHORT usLengthOutput;               //length of complete output structure
  USHORT usTmtXRc;                     //function returncode
} TMX_PREFIX_OUT, * PTMX_PREFIX_OUT, XOUT, * PXOUT;

//======================================================
typedef struct _TMX_CREATE
{
  USHORT usThreshold;
  CHAR szDataName[MAX_EQF_PATH];
  CHAR szIndexName[MAX_EQF_PATH];
  CHAR szSourceLanguage[MAX_LANG_LENGTH];
  CHAR szDescription[MAX_DESCRIPTION];
} TMX_CREATE, * PTMX_CREATE;

typedef struct _TMX_CREATE_IN
{
  TMX_PREFIX_IN  stPrefixIn;
  TMX_CREATE stTmCreate;
} TMX_CREATE_IN, * PTMX_CREATE_IN;

typedef struct _TMX_CREATE_OUT
{
  TMX_PREFIX_OUT  stPrefixOut;
  PTMX_CLB pstTmClb;
} TMX_CREATE_OUT, * PTMX_CREATE_OUT;

//=======================================================================
typedef struct _TMX_OPEN
{
  CHAR szDataName[MAX_EQF_PATH];
  CHAR szIndexName[MAX_EQF_PATH];
  CHAR szServer[MAX_SERVER_NAME];
  CHAR szUserid[MAX_USERID];
  USHORT usAccess;
  USHORT usThreshold;
} TMX_OPEN, * PTMX_OPEN;

typedef struct _TMX_OPEN_IN
{
  TMX_PREFIX_IN stPrefixIn;
  TMX_OPEN stTmOpen;
} TMX_OPEN_IN, * PTMX_OPEN_IN;

typedef struct _TMX_OPEN_OUT
{
  TMX_PREFIX_OUT stPrefixOut;
  PTMX_CLB pstTmClb;
} TMX_OPEN_OUT, * PTMX_OPEN_OUT;

//=======================================================================
typedef struct _TMX_CLOSE_IN
{
  TMX_PREFIX_IN stPrefixIn;
} TMX_CLOSE_IN, * PTMX_CLOSE_IN;

typedef struct _TMX_CLOSE_OUT
{
  TMX_PREFIX_OUT stPrefixOut;
} TMX_CLOSE_OUT, * PTMX_CLOSE_OUT;

//=======================================================================
typedef struct _TMX_PUT
{
  CHAR      szSource[MAX_SEGMENT_SIZE];        //source sentence
  CHAR      szTarget[MAX_SEGMENT_SIZE];        //target sentence
  CHAR      szSourceLanguage[MAX_LANG_LENGTH]; //language name of source
  CHAR      szTargetLanguage[MAX_LANG_LENGTH]; //language name of target
  CHAR      szAuthorName[MAX_USERID];          //author name of target
  USHORT    usTranslationFlag;                 /* type of translation, 0 = human, 1 = machine, 2 = GobalMemory */
  CHAR      szFileName[MAX_FILESPEC];          //where source comes from name+ext
  LONG_FN   szLongName;                        // name of source file (long name or EOS)
  USHORT    usSourceSegmentId;                 //seg. num. of source sentence from analysis
  CHAR      szTagTable[MAX_FNAME];             //tag table name
  TIME_L    lTime;                             //time stamp
} TMX_PUT, * PTMX_PUT;


typedef struct _TMX_PUT_W
{
  CHAR_W    szSource[MAX_SEGMENT_SIZE];        //source sentence
  CHAR_W    szTarget[MAX_SEGMENT_SIZE];        //target sentence
  CHAR      szSourceLanguage[MAX_LANG_LENGTH]; //language name of source
  CHAR      szTargetLanguage[MAX_LANG_LENGTH]; //language name of target
  CHAR      szAuthorName[MAX_USERID];          //author name of target
  USHORT    usTranslationFlag;                 /* type of translation, 0 = human, 1 = machine, 2 = GobalMemory */
  CHAR      szFileName[MAX_FILESPEC];          //where source comes from name+ext
  LONG_FN   szLongName;                        // name of source file (long name or EOS)
  ULONG     ulSourceSegmentId;                 //seg. num. of source sentence from analysis
  CHAR      szTagTable[MAX_FNAME];             //tag table name
  TIME_L    lTime;                             //time stamp
  CHAR_W    szContext[MAX_SEGMENT_SIZE];       //segment context
  CHAR_W    szAddInfo[MAX_SEGMENT_SIZE];       // additional segment information
  BOOL      fMarkupChanged;                    // Markup does not exist, changed to OTMUTF8 during import
} TMX_PUT_W, * PTMX_PUT_W;


typedef struct _TMX_PUT_IN
{
  TMX_PREFIX_IN  stPrefixIn;           //input prefix
  TMX_PUT        stTmPut;             //pointer to put input structure
} TMX_PUT_IN, * PTMX_PUT_IN;

typedef struct _TMX_PUT_IN_W
{
  TMX_PREFIX_IN  stPrefixIn;           //input prefix
  TMX_PUT_W      stTmPut;             //pointer to put input structure
} TMX_PUT_IN_W, * PTMX_PUT_IN_W;


//structure TMX_PUT_OUT
typedef struct _TMX_PUT_OUT
{
  TMX_PREFIX_OUT stPrefixOut;           //output structure
} TMX_PUT_OUT, * PTMX_PUT_OUT;

typedef struct _TMX_PUT_OUT_W
{
  TMX_PREFIX_OUT stPrefixOut;           //output structure
} TMX_PUT_OUT_W, * PTMX_PUT_OUT_W;


//=======================================================================
//structure TMX_GET_IN and _TMX_GET
typedef struct _TMX_GET
{
  CHAR        szSource[MAX_SEGMENT_SIZE];        //source sentence
  CHAR        szTagTable[MAX_FNAME];             //tag table name of source
  CHAR        szSourceLanguage[MAX_LANG_LENGTH]; //language of source
  CHAR        szFileName[MAX_FILESPEC];          //file name the source comes from
  LONG_FN     szLongName;                        // name of source file (long name or EOS)
  USHORT      usSegmentId;                       //segment number from analysis
  CHAR        szAuthorName[MAX_USERID];          //author name
  CHAR        szTargetLanguage[MAX_LANG_LENGTH]; //language of translation
  USHORT      usRequestedMatches;                //number of requested matches
  USHORT      usMatchThreshold;                  //threshold for match level
  USHORT      usConvert;                //how the output should be converted
  USHORT      usParm;                   //for future use, xmp. GET_ONLY_MT_MATCHES, GET_ONLY_EXACT_MATCHES...)
} TMX_GET, * PTMX_GET;

typedef struct _TMX_GET_W
{
  CHAR_W      szSource[MAX_SEGMENT_SIZE];        //source sentence
  CHAR        szTagTable[MAX_FNAME];             //tag table name of source
  CHAR        szSourceLanguage[MAX_LANG_LENGTH]; //language of source
  CHAR        szFileName[MAX_FILESPEC];          //file name the source comes from
  LONG_FN     szLongName;                        // name of source file (long name or EOS)
  ULONG       ulSegmentId;                       //segment number from analysis
  CHAR        szAuthorName[MAX_USERID];          //author name
  CHAR        szTargetLanguage[MAX_LANG_LENGTH]; //language of translation
  USHORT      usRequestedMatches;                //number of requested matches
  USHORT      usMatchThreshold;                  //threshold for match level
  USHORT      usConvert;                //how the output should be converted
  ULONG       ulParm;                   //for future use, xmp. GET_ONLY_MT_MATCHES, GET_ONLY_EXACT_MATCHES...)
  CHAR_W      szContext[MAX_SEGMENT_SIZE];       //segment context
  CHAR_W      szAddInfo[MAX_SEGMENT_SIZE];       // additional segment information
  ULONG       ulSrcOemCP;
  ULONG       ulTgtOemCP;
  PVOID       pvReplacementList;                 // ptr to a SGML-DITA replacement list or NULL
  PVOID       pvGMOptList;                       // ptr to a global memory option list or NULL
  bool fSourceLangIsPrefered;
  bool fTargetLangIsPrefered;
} TMX_GET_W, * PTMX_GET_W;

typedef struct _TMX_GET_IN
{
  TMX_PREFIX_IN  stPrefixIn;           //prefix of each command
  TMX_GET        stTmGet;             //pointer in structure
} TMX_GET_IN, * PTMX_GET_IN;

typedef struct _TMX_GET_IN_W
{
  TMX_PREFIX_IN  stPrefixIn;           //prefix of each command
  TMX_GET_W        stTmGet;             //pointer in structure
} TMX_GET_IN_W, * PTMX_GET_IN_W;


//=======================================================================
// structure TMX_GET_OUT
typedef struct _TMX_MATCH_TABLE
{
  CHAR   szSource[MAX_SEGMENT_SIZE];   //source sentence with tags
  CHAR   szFileName[MAX_FILESPEC];     //file name where the source comes from.
  LONG_FN szLongName;                  // name of source file (long name or EOS)
  USHORT usSegmentId;                  //segment number from analysis
  CHAR   szTarget[MAX_SEGMENT_SIZE];   //target sentence with tags
  CHAR   szTargetLanguage[MAX_LANG_LENGTH]; //language of translation
  USHORT    usTranslationFlag;                 /* type of translation, 0 = human, 1 = machine, 2 = GobalMemory */
  CHAR   szTargetAuthor[MAX_USERID];   //author name of target
  TIME_L lTargetTime;                  //time stamp of target
  USHORT usMatchLevel;                 //similarity of the source
  USHORT usOverlaps;                   //temp field - nr of overlapping triples
  CHAR   szTagTable[MAX_FNAME];        //tag table name of source
  ULONG  ulKey;                        // key of match
  USHORT usTargetNum;                  // number of target
  USHORT usDBIndex;                    // number of memory in current hierarchy
} TMX_MATCH_TABLE, * PTMX_MATCH_TABLE;

typedef struct _TMX_MATCH_TABLE_W
{
  CHAR_W  szSource[MAX_SEGMENT_SIZE];   //source sentence with tags
  CHAR    szFileName[MAX_FILESPEC];     //file name where the source comes from.
  LONG_FN szLongName;                   // name of source file (long name or EOS)
  ULONG   ulSegmentId;                  //segment number from analysis
  CHAR_W  szTarget[MAX_SEGMENT_SIZE];   //target sentence with tags
  CHAR    szTargetLanguage[MAX_LANG_LENGTH]; //language of translation
  CHAR    szOriginalSrcLanguage[MAX_LANG_LENGTH]; //language of src of translation
  USHORT    usTranslationFlag;                 /* type of translation, 0 = human, 1 = machine, 2 = GobalMemory */
  CHAR    szTargetAuthor[MAX_USERID];   //author name of target
  TIME_L  lTargetTime;                  //time stamp of target
  USHORT  usMatchLevel;                 //similarity of the source
  int iWords;
  int iDiffs;
  USHORT  usOverlaps;                   //temp field - nr of overlapping triples
  CHAR    szTagTable[MAX_FNAME];        //tag table name of source
  ULONG   ulKey;                        // key of match
  USHORT  usTargetNum;                  // number of target
  USHORT  usDBIndex;                    // number of memory in current hierarchy
  CHAR_W  szContext[MAX_SEGMENT_SIZE];  // segment context info
  CHAR_W  szAddInfo[MAX_SEGMENT_SIZE];  // additional segment information
  USHORT  usContextRanking;             // context ranking from user exit context processing
  USHORT  usMatchInfo;                  // for future use: special info for match
} TMX_MATCH_TABLE_W, * PTMX_MATCH_TABLE_W;

typedef struct _TMX_GET_OUT
{
  TMX_PREFIX_OUT stPrefixOut;         //prefix of Output buffer
  USHORT usNumMatchesFound;           //number of matches found
  TMX_MATCH_TABLE stMatchTable[MAX_MATCHES];     //match structure
  USHORT fsAvailFlags;                // additional flags (more exact/fuzzy matches avail)
} TMX_GET_OUT, * PTMX_GET_OUT;

typedef struct _TMX_GET_OUT_W
{
  TMX_PREFIX_OUT    stPrefixOut;               //prefix of Output buffer
  USHORT            usNumMatchesFound;         //number of matches found
  TMX_MATCH_TABLE_W stMatchTable[MAX_MATCHES]; //match structure
  USHORT fsAvailFlags;                         // additional flags (more exact/fuzzy matches avail)
} TMX_GET_OUT_W, * PTMX_GET_OUT_W;






//=======================================================================
/**********************************************************************/
/* Attention: for special names mode of TMExtract, the TMX_EXT_IN     */
/*            structure is used in a different way:                   */
/*            usConvert contains the ID of the names to extract:      */
/*              MEM_OUTPUT_TAGTABLES  return list of tag tables of TM */
/*              MEM_OUTPUT_AUTHORS    return list of authors of TM    */
/*              MEM_OUTPUT_DOCUMENTS  return list of documents of TM  */
/*              MEM_OUTPUT_LANGUAGES  return list of languages of TM  */
/*            usNextTarget contains 0 for the first call or the       */
/*            index returned in the usNextTarget field of the         */
/*            TMX_EXT_OUT structure for subsequent calls if more      */
/*            names are available than fit into the output buffers.   */
/*            The remining fields are unused.                         */
/**********************************************************************/
//structure TMX_EXT_IN
typedef struct _TMX_EXT_IN
{
  TMX_PREFIX_IN stPrefixIn;      //prefix of input buffer
  ULONG ulTmKey;                 //tm get to get
  USHORT usConvert;              //how the output is to appear
  USHORT usNextTarget;           //which target record to address next
} TMX_EXT_IN, * PTMX_EXT_IN;
typedef TMX_EXT_IN TMX_EXT_IN_W, *PTMX_EXT_IN_W;
//=======================================================================
/**********************************************************************/
/* Attention: for special names mode of TMExtract, the TMX_EXT_OUT    */
/*            structure is used in a different way:                   */
/*            szSource and szTarget contain a null terminated list    */
/*            of names (NULL-terminated strings followed by another   */
/*            NULL).                                                  */
/*            fMachineTranslation is TRUE if more names are available */
/*            usNextTarget gives the index of the next name if more   */
/*            names are available than fit into the output buffers    */
/*            The remaining fields are unused.                        */
/**********************************************************************/
// structure TMX_EXT_OUT
typedef struct _TMX_EXT
{
  CHAR      szSource[MAX_SEGMENT_SIZE];        //source sentence
  CHAR      szTarget[MAX_SEGMENT_SIZE];        //target sentence
  CHAR      szTagTable[MAX_FNAME];             //tag table name
  CHAR      szTargetLanguage[MAX_LANG_LENGTH]; //language name of target
  CHAR      szAuthorName[MAX_USERID];          //author name of target
  USHORT  usTranslationFlag; /* type of translation, 0 = human, 1 = machine, 2 = Global Memory */
  CHAR      szFileName[MAX_FILESPEC];          //where source comes from name+ext
  LONG_FN   szLongName;                        // name of source file (long name or EOS)
  USHORT    usSourceSegmentId;                 //seg. num. of source sentence from analysis
  TIME_L    lTargetTime;                       //time stamp of target
} TMX_EXT, * PTMX_EXT;


typedef struct _TMX_EXT_W
{
  CHAR_W    szSource[MAX_SEGMENT_SIZE];        //source sentence
  CHAR_W    szTarget[MAX_SEGMENT_SIZE];        //target sentence
  CHAR      szOriginalSourceLanguage[MAX_LANG_LENGTH]; //language name of the source
  CHAR      szTagTable[MAX_FNAME];             //tag table name
  CHAR      szTargetLanguage[MAX_LANG_LENGTH]; //language name of target
  CHAR      szAuthorName[MAX_USERID];          //author name of target
  USHORT  usTranslationFlag; /* type of translation, 0 = human, 1 = machine, 2 = Global Memory */
  CHAR      szFileName[MAX_FILESPEC];          //where source comes from name+ext
  LONG_FN   szLongName;                        // name of source file (long name or EOS)
  ULONG     ulSourceSegmentId;                 //seg. num. of source sentence from analysis
  TIME_L    lTargetTime;                       //time stamp of target
  CHAR_W    szContext[MAX_SEGMENT_SIZE];       //segment context
  CHAR_W    szAddInfo[MAX_SEGMENT_SIZE];       // additional segment information
} TMX_EXT_W, * PTMX_EXT_W;

typedef struct _TMX_EXT_OUT
{
  TMX_PREFIX_OUT stPrefixOut;      //prefix of output buffer
  TMX_EXT stTmExt;                 //pointer to put structure
  CHAR szServer[MAX_SERVER_NAME];  //server name filled by u-code function
  ULONG ulTmKey;                   //tm record key
  USHORT usNextTarget;             //which target record to address next
  ULONG ulMaxEntries;              //number of entries in tm data file
} TMX_EXT_OUT, * PTMX_EXT_OUT;

typedef struct _TMX_EXT_OUT_W
{
  TMX_PREFIX_OUT stPrefixOut;      //prefix of output buffer
  TMX_EXT_W      stTmExt;          //pointer to put structure
  CHAR szServer[MAX_SERVER_NAME];  //server name filled by u-code function
  ULONG ulTmKey;                   //tm record key
  USHORT usNextTarget;             //which target record to address next
  ULONG ulMaxEntries;              //number of entries in tm data file
} TMX_EXT_OUT_W, *PTMX_EXT_OUT_W;


//=======================================================================

/**********************************************************************/
/* TMX_INFO_IN, TMX_INFO_OUT used by TmInfo                           */
/**********************************************************************/
typedef struct  _TMX_INFO_IN
{
  TMX_PREFIX_IN stPrefixIn;
  USHORT        usInfoLevel;
} TMX_INFO_IN, * PTMX_INFO_IN;

typedef struct _TMX_INFO_OUT
{
  TMX_PREFIX_OUT stPrefixOut;
  TMX_SIGN       stTmSign;
  USHORT         usThreshold;
} TMX_INFO_OUT , * PTMX_INFO_OUT;

/**********************************************************************/
/* _TMX_DELTM_IN and _TMX_DELTM_IN  used bt TmDeleteTM                */
/**********************************************************************/
typedef struct _TMX_DELTM_IN
{
  TMX_PREFIX_IN stPrefixIn;
  CHAR         szFullTmName[MAX_EQF_PATH];
  CHAR         szFullIndexName[MAX_EQF_PATH];
  CHAR         szFullPropName[MAX_EQF_PATH];
} TMX_DELTM_IN, * PTMX_DELTM_IN;

typedef struct _TMXDELTM_OUT
{
  TMX_PREFIX_OUT stPrefixOut;
} TMX_DELTM_OUT, * PTMX_DELTM_OUT;


//#define PROP_NTM_SZ_FULL_MEM_NAME_SIZE MAX_EQF_PATH
#define PROP_NTM_SZ_FULL_MEM_NAME_SIZE 54
/**********************************************************************/
/* TM property structure                                              */
/**********************************************************************/
typedef struct _PROP_NTM
{
  PROPHEAD stPropHead;
  TMX_SIGN stTMSignature;
  CHAR     szNTMMarker[sizeof(NTM_MARKER)];
  USHORT   usThreshold;

} PROP_NTM, *PPROP_NTM;

// last used values
typedef struct _MEM_LAST_USED
{
  // Do only insert new values at the end of the stucture !!!!!!!!!!
  PROPHEAD stPropHead;                        // Common header of properties
  CHAR     szFormat[MAX_FILESPEC];            // Create dialog: last used format table
  CHAR     szExclusion[MAX_FILESPEC];         // Create dialog: last used exclusion list
  LANGUAGE szSourceLang;                      // Create dialog: last used source language
  LANGUAGE szTargetLang;                      // Create dialog: last used target language
  CHAR     szDrive[MAX_FILESPEC];             // Create dialog: last used local disk drive
  CHAR     szExpDriveLastUsed[MAX_DRIVE];     // Export dialog: last used drive format: ~x:~
  CHAR     szExpDirLastUsed[_MAX_DIR];        // Export dialog: last used directory format: ~\xxx\yyy\~
  // Structure end in Troja 2.1
  CHAR     szIncludeServer[MAX_SERVER_NAME];  // Include dialog: Last used server ~SSER0545~
  CHAR     szCreateServer[MAX_SERVER_NAME];   // Create dialog: Last used server ~SSER0545~
  BOOL     usCreateLocation;                  // Create dialog: Possible values: TM_LOCAL, TM_REMOTE
  CHAR     szRemoteDrive[MAX_FILESPEC];       // Create dialog: last used remote disk drive
  // Structure end in Troja 3.0
  CHAR     szImpPathLastUsed[MAX_PATH144];    // Import dlg: last used path
                                              // x:\xx
  // Structure end in Troja 3.c
  USHORT   usExpMode;                         // last used export mode
  USHORT   usImpMode;                         // last used import mode
  CHAR     szImpPathLastUsed2[MAX_LONGPATH];  // Import dlg: last used path (long)
}MEM_LAST_USED, * PMEM_LAST_USED;




USHORT  TmGetServerDrives( PDRIVES_IN  pDrivesIn,      // Pointer to DRIVES_IN struct
                           PDRIVES_OUT pDrivesOut,     // Pointer to DRIVES_OUT struct
                           USHORT      usMsgHandling );// Message handling parameter
USHORT  TmGetServerDrivesHwnd( PDRIVES_IN, PDRIVES_OUT, USHORT, HWND );
USHORT  TmGetServerTMs( PFILE_LIST_IN  pTmListIn,      // Pointer to FILE_LIST_IN struct !!! CHM
                        PFILE_LIST_OUT pTmListOut,     // Pointer to FILE_LIST_OUT struct !!! CHM
                        USHORT       usMsgHandling );  // Message handling parameter
USHORT  TmGetTMPart( HTM          htm,                 // Memory database handle
                     PSZ          pszMemPat,           // Full translation memory path
                     PGETPART_IN  pGetPartIn,          // Pointer to GETPART_IN struct
                     PGETPART_OUT pGetPartOut,         // Pointer to GETPART_OUT struct
                     USHORT       usMsgHandling );     // Message handling parameter
USHORT  TmSendTMProp( SERVERNAME szServer,             // Servername
                      PSZ        pszMemName,           // Translation memory name
                      USHORT     usMsgHandling );      // Message handling parameter
USHORT  TmReceiveTMProp( SERVERNAME szServer,          // Servername
                         PSZ        pszMemName,        // Translation memory name
                         USHORT     usMsgHandling );       // Message handling parameter

//use this define as usMsgHandling for special handling of greyedout TMs
#define DELETE_GREYEDOUT 2

USHORT  TmDeleteFile( SERVERNAME szServer,             // Servername
                      PSZ        pszFilePath,          // Full file path
                      USHORT     usMsgHandling );      // Message handling parameter
USHORT TmGetServerFileInfo( SERVERNAME   szServer,        //Servername
                            PSZ          pszFilePath,     //Full file path
                            PFILEFINDBUF pstFile,        // File info
                            USHORT       usMsgHandling ); // Message handling parameter
USHORT TmGetServerFileInfoHwnd( SERVERNAME, PSZ, PFILEFINDBUF, USHORT, HWND );
USHORT TmCompareLocalRemoteProperties( SERVERNAME, PSZ, USHORT );
USHORT MemRcHandling( USHORT,  PSZ, HTM *, PSZ );
USHORT MemRcHandlingHwnd( USHORT,  PSZ, HTM *, PSZ, HWND );

/**********************************************************************/
/* MemReadWriteSegment                                                */
/**********************************************************************/
USHORT
MemReadWriteSegment( HTM,
                     PSZ,
                     HTM,
                     PSZ,
                     PEXT_IN,
                     PEXT_OUT,
                     PTMX_PUT_IN,
                     PTMX_PUT_OUT,
                     ULONG *,
                     ULONG *,
                     TIME_L,
                     PSZ,
                     PSZ,
                     PSZ,
                     BOOL );
USHORT
MemReadWriteSegmentHwnd( HTM,
                     PSZ,
                     HTM,
                     PSZ,
                     PEXT_IN,
                     PEXT_OUT,
                     PTMX_PUT_IN,
                     PTMX_PUT_OUT,
                     ULONG *,
                     ULONG *,
                     TIME_L,
                     PSZ,
                     PSZ,
                     PSZ,
                     BOOL,
                     HWND );


/**********************************************************************/
/* NTMReadWriteSegment                                                */
/**********************************************************************/
// message handling flags for NTMReadWriteSegment :
//   TMRWS_NOMSG:    show no error message at all
//   TMRWS_ALLMSG:   show all error messages
//   TMRWS_WRITEMSG: show only error messages for write segment (for TM organize!)
#define TMRWS_NOMSG    0
#define TMRWS_ALLMSG   1
#define TMRWS_WRITEMSG 2

USHORT NTMReadWriteSegmentW( HTM,          //Handle of Input TM
                             PSZ,          //Full path to Input TM
                             HTM,          //Handle of Output TM
                             PSZ,          //Full path to Output TM
                             PTMX_EXT_IN_W,//Pointer to the EXTRACT_IN structure
                             PTMX_EXT_OUT_W, //Pointer to the EXTRACT_OUT structure
                             PTMX_PUT_IN_W,  //Pointer to the REPLACE_OUT structure
                             PTMX_PUT_OUT_W, //Pointer to the REPLACE_OUT structure
                             ULONG *,      //Pointer to a segment counter
                             ULONG *,      //Pointer to the invalid segment counter
                             PSZ,          //pointer to TM source language
                             USHORT );     //message handling flags
USHORT NTMReadWriteSegmentHwndW( HTM,      //Handle of Input TM
                             PSZ,          //Full path to Input TM
                             HTM,          //Handle of Output TM
                             PSZ,          //Full path to Output TM
                             PTMX_EXT_IN_W,  //Pointer to the EXTRACT_IN structure
                             PTMX_EXT_OUT_W, //Pointer to the EXTRACT_OUT structure
                             PTMX_PUT_IN_W,  //Pointer to the REPLACE_OUT structure
                             PTMX_PUT_OUT_W, //Pointer to the REPLACE_OUT structure
                             ULONG *,      //Pointer to a segment counter
                             ULONG *,      //Pointer to the invalid segment counter
                             PSZ,          //pointer to TM source language
                             USHORT,       //message handling flags
                             HWND );       //handle for error messages parent



BOOL fMemIsAvail( PSZ, PSZ, PSZ );      // memory is available and accessible
USHORT MemFillCBNames( HWND, PSZ, PSZ );
USHORT MemFillTableLB( HWND   hListBox, USHORT usBoxType, PSZ    pszLastUsed );

/**********************************************************************/
/* TmCreate                                                           */
/**********************************************************************/
USHORT TmCreate( PSZ, HTM *, HTM, PSZ, PSZ, PSZ, PSZ, USHORT, HWND );

/**********************************************************************/
/* TmOpen                                                             */
/**********************************************************************/
USHORT TmOpen( PSZ, HTM *, USHORT, USHORT,    //(in)  location:    TM_LOCAL
                   //                   TM_REMOTE
                   //                   TM_LOCAL_REMOTE
        USHORT,    //(in)  message handling parameter
                   //      TRUE:  display error message
                   //      FALSE: display no error message
        HWND   );  //(in)  window handle for error messages

/**********************************************************************/
/* TmClose                                                            */
/**********************************************************************/
USHORT
TmClose( HTM,        //(in) TM handle returned from open
         PSZ,        //(in) full TM name x:\eqf\mem\mem.mem
         USHORT,     //(in) message handling parameter
                     //     TRUE:  display error message
                     //     FALSE: display no error message
         HWND );     //(in) window handle for error messages
/**********************************************************************/
/* TmReplace                                                          */
/**********************************************************************/
USHORT
TmReplace( HTM,           //(in)  TM handle
           PSZ,           //(in)  full TM name x:\eqf\mem\mem.mem
           PTMX_PUT_IN,   //(in)  pointer to put input structure
           PTMX_PUT_OUT,  //(out) pointer to put output structure
           USHORT );      //(in)  message handling parameter
                          //      TRUE:  display error message
                          //      FALSE: display no error message
USHORT
TmReplace( HTM, PSZ, PTMX_PUT_IN_W, PTMX_PUT_OUT_W, USHORT );

USHORT
TmReplace( HTM,           //(in)  TM handle
           PSZ,           //(in)  full TM name x:\eqf\mem\mem.mem
           PTMX_PUT_IN,   //(in)  pointer to put input structure
           PTMX_PUT_OUT,  //(out) pointer to put output structure
           USHORT,        //(in)  message handling parameter
                          //      TRUE:  display error message
                          //      FALSE: display no error message
           HWND );                     //(in) handle for error messages

USHORT
TmReplace( HTM, PSZ, PTMX_PUT_IN_W, PTMX_PUT_OUT_W, USHORT, HWND );

/**********************************************************************/
/* TmGet                                                              */
/**********************************************************************/
USHORT
TmGetW(HTM,               //(in)  TM handle
       PSZ,               //(in)  full TM name x:\eqf\mem\mem.tmd
       PTMX_GET_IN_W,     //(in)  pointer to get input structure
       PTMX_GET_OUT_W,    //(out) pointer to get output structure
       USHORT );          //(in)  message handling parameter
                          //      TRUE:  display error message
                          //      FALSE: display no error message

USHORT
TmGet( HTM,               //(in)  TM handle
       PSZ,               //(in)  full TM name x:\eqf\mem\mem.tmd
       PTMX_GET_IN,       //(in)  pointer to get input structure
       PTMX_GET_OUT,      //(out) pointer to get output structure
       USHORT );          //(in)  message handling parameter
                          //      TRUE:  display error message
                          //      FALSE: display no error message
/**********************************************************************/
/* TmExtract                                                          */
/**********************************************************************/
USHORT
TmExtract( HTM,
           PSZ,
           PTMX_EXT_IN,
           PTMX_EXT_OUT,
           USHORT );

USHORT
TmExtractW( HTM, PSZ, PTMX_EXT_IN_W, PTMX_EXT_OUT_W, USHORT );


USHORT
TmExtractHwnd( HTM,
           PSZ,
           PTMX_EXT_IN,
           PTMX_EXT_OUT,
           USHORT,
           HWND );                     //(in) handle for error messages

USHORT
TmExtractHwndW( HTM, PSZ, PTMX_EXT_IN_W, PTMX_EXT_OUT_W, USHORT, HWND );

/**********************************************************************/
/* information levels for TmInfo function call                        */
/* TM_INFO_SIGNATURE - returns the signature record of a TM           */
/**********************************************************************/
#define TMINFO_SIGNATURE 0

/**********************************************************************/
/* TmInfo                                                             */
/**********************************************************************/
USHORT TmInfo( HTM, PSZ, USHORT, PTMX_INFO_IN, PTMX_INFO_OUT, USHORT );
USHORT TmInfoHwnd( HTM, PSZ, USHORT, PTMX_INFO_IN, PTMX_INFO_OUT, USHORT, HWND );

/**********************************************************************/
/* TmDeleteTM                                                         */
/**********************************************************************/
USHORT TmDeleteTM( PSZ, USHORT, HWND, PUSHORT );

/**********************************************************************/
/* TmDeleteSegment                                                    */
/**********************************************************************/
USHORT
TmDeleteSegment( HTM,
                 PSZ,
                 PTMX_PUT_IN,
                 PTMX_PUT_OUT,
                 USHORT );

USHORT
TmDeleteSegmentW( HTM, PSZ, PTMX_PUT_IN_W, PTMX_PUT_OUT_W, USHORT );



/**********************************************************************/
/* NTMConvertCRLF                                                     */
/**********************************************************************/
VOID
NTMConvertCRLF( PSZ,
                PSZ,
                USHORT );
VOID NTMConvertCRLFW( PSZ_W, PSZ_W, USHORT );


/**********************************************************************/
/* NTMOpenProperties                                                  */
/**********************************************************************/
USHORT
NTMOpenProperties( HPROP *,
                   PVOID *,
                   PSZ,
                   PSZ,
                   USHORT,
                   BOOL );

// functions dealing with long document tables
USHORT NTMCreateLongNameTable( PTMX_CLB pTmClb );
USHORT NTMReadLongNameTable( PTMX_CLB pTmClb );
USHORT NTMWriteLongNameTable( PTMX_CLB pTmClb );
USHORT NTMDestroyLongNameTable( PTMX_CLB pTmClb );
USHORT NTMCreateLangGroupTable( PTMX_CLB pTmClb );
USHORT NTMAddLangGroup( PTMX_CLB pTmClb, PSZ pszLang, USHORT sLangID );
USHORT NTMOrganizeIndexFile
(
  PTMX_CLB pTmClb               // ptr to control block,
);

USHORT NTMOrganizeIndexFile1
(
  PTMX_CLB pTmClb               // ptr to control block,
);

// Update specific parts of segment

// flags controlling the updated segment parts
#define  TMUPDSEG_MARKUP       0x01    // update markup/tag table
#define  TMUPDSEG_MTFLAG       0x02    // update MT flag
#define  TMUPDSEG_TARGLANG     0x04    // update target language
#define  TMUPDSEG_DATE         0x08    // update segment time

USHORT TmUpdSeg
(
  HTM         htm,                       //(in)  TM handle
  PSZ         szMemPath,                 //(in)  full TM name x:\eqf\mem\mem
  PTMX_PUT_IN pstPutIn,                  //(in)  pointer to put input structure
  ULONG       ulUpdKey,                  //(in)  key of record being updated
  USHORT      usUpdTarget,               //(in)  number of target being updated
  USHORT      usFlags,                   //(in)  flags controlling the updated fields
  USHORT      usMsgHandling              //(in)  message handling parameter
                                         //      TRUE:  display error message
                                         //      FALSE: display no error message
);

USHORT TmUpdSegHwnd
(
  HTM         htm,                       //(in)  TM handle
  PSZ         szMemPath,                 //(in)  full TM name x:\eqf\mem\mem
  PTMX_PUT_IN pstPutIn,                  //(in)  pointer to put input structure
  ULONG       ulUpdKey,                  //(in)  key of record being updated
  USHORT      usUpdTarget,               //(in)  number of target being updated
  USHORT      usFlags,                   //(in)  flags controlling the updated fields
  USHORT      usMsgHandling,             //(in)  message handling parameter
                                         //      TRUE:  display error message
                                         //      FALSE: display no error message
  HWND        hwnd                       //(in)  handle for error messages
);

USHORT TmUpdSegW
(
  HTM         htm,                       //(in)  TM handle
  PSZ         szMemPath,                 //(in)  full TM name x:\eqf\mem\mem
  PTMX_PUT_IN_W pstPutIn,                  //(in)  pointer to put input structure
  ULONG       ulUpdKey,                  //(in)  key of record being updated
  USHORT      usUpdTarget,               //(in)  number of target being updated
  USHORT      usFlags,                   //(in)  flags controlling the updated fields
  USHORT      usMsgHandling              //(in)  message handling parameter
                                         //      TRUE:  display error message
                                         //      FALSE: display no error message
);

USHORT TmUpdSegHwndW
(
  HTM         htm,                       //(in)  TM handle
  PSZ         szMemPath,                 //(in)  full TM name x:\eqf\mem\mem
  PTMX_PUT_IN_W pstPutIn,                  //(in)  pointer to put input structure
  ULONG       ulUpdKey,                  //(in)  key of record being updated
  USHORT      usUpdTarget,               //(in)  number of target being updated
  USHORT      usFlags,                   //(in)  flags controlling the updated fields
  USHORT      usMsgHandling,             //(in)  message handling parameter
                                         //      TRUE:  display error message
                                         //      FALSE: display no error message
  HWND        hwnd                       //(in)  handle for error messages
);



// structure for MT_TMMERGE pointer
typedef struct _MT_TMMERGE
{
  CHAR        chMemory[MAX_EQF_PATH];            // TM name to be merged into
  CHAR        chSGMLFile[MAX_EQF_PATH];          // external memory
  OBJNAME     szObjName;                         // document object name
  HWND        hwndNotify;                        // parent to be notified
  CHAR        szTargetLang[MAX_LANG_LENGTH];
  OBJNAME     szFolObjName;                      // object name of folder
} MT_TMMERGE, *PMT_TMMERGE;

BOOL MTTMMergeStart
(
  PLISTCOMMAREA pCommArea,
  PMT_TMMERGE pTMMerge
);
BOOL MemCreatePath( PSZ pszString );


// Unicode additions
VOID TMX_GET_IN_Unicode2ASCII( PTMX_GET_IN_W pstGetInW, PTMX_GET_IN pstGetIn, ULONG ulCP );
VOID TMX_GET_OUT_Unicode2ASCII( PTMX_GET_OUT_W pstGetOutW, PTMX_GET_OUT pstGetOut, ULONG ulCP );
VOID TMX_GET_IN_ASCII2Unicode( PTMX_GET_IN pstGetIn, PTMX_GET_IN_W pstGetInW, ULONG  ulCP );
VOID TMX_GET_OUT_ASCII2Unicode( PTMX_GET_OUT pstGetOut, PTMX_GET_OUT_W pstGetOutW, ULONG ulCP );

VOID  TMX_PUT_IN_Unicode2ASCII( PTMX_PUT_IN_W pstPutInW, PTMX_PUT_IN pstPutIn, ULONG ulCP );
VOID  TMX_PUT_OUT_ASCII2Unicode( PTMX_PUT_OUT pstPutOut, PTMX_PUT_OUT_W pstPutOutW );
VOID  TMX_PUT_IN_ASCII2Unicode( PTMX_PUT_IN pstPutIn, PTMX_PUT_IN_W pstPutInW , ULONG ulCP);
VOID  TMX_PUT_OUT_Unicode2ASCII( PTMX_PUT_OUT_W pstPutOutW, PTMX_PUT_OUT pstPutOut );
VOID  TMX_EXT_IN_Unicode2ASCII( PTMX_EXT_IN_W pstExtInW, PTMX_EXT_IN pstExtIn );
VOID  TMX_EXT_OUT_ASCII2Unicode( PTMX_EXT_OUT pstExtOut, PTMX_EXT_OUT_W pstExtOutW, ULONG ulCP );
VOID  TMX_EXT_IN_ASCII2Unicode( PTMX_EXT_IN pstExtIn, PTMX_EXT_IN_W pstExtInW );
VOID  TMX_EXT_OUT_Unicode2ASCII( PTMX_EXT_OUT_W pstExtOutW, PTMX_EXT_OUT pstExtOut, ULONG ulCP );

VOID  TMX_PUT_IN_ASCII2Unicode( PTMX_PUT_IN pstDelIn, PTMX_PUT_IN_W pstDelInW, ULONG ulCP );
VOID  TMX_PUT_OUT_Unicode2ASCII( PTMX_PUT_OUT_W pstDelOutW, PTMX_PUT_OUT pstDelOut );

// function to convert the memory to the new format
USHORT MemConvertMem( PSZ pszFullMemName );

// return codes of function MemConvertMem

// memory converted successfully
#define MEM_CONVERTMEM_SUCCESS  0

// memory conversion not required, memory is in new format already
#define MEM_CONVERTMEM_ALREADYNEWFORMAT 7001


// do a cleanup of temporary memories
void TMCleanupTempMem
(
  PSZ         pszPrefix                                     // ptr to memory prefix
);

// create a temporary memory
USHORT TMCreateTempMem
(
  PSZ         pszPrefix,                                    // short prefix to be used for memory name (should start with a dollar sign)
  PSZ         pszMemPath,                                   // ptr to buffer for memory path
  HTM         *pHtm,                                        // ptr to buffer for memory handle
  HTM         htm,                                          // htm of similar memory
  PSZ         pszSourceLang,                                // memory source language
  HWND        hwnd                                          // window handle for error messages
);

// delete a temporary memory
void TMDeleteTempMem
(
  PSZ         pszMemPath                                    // ptr to memory path
);

BOOL TMFuzzynessEx
(
  PSZ pszMarkup,                       // markup table name
  PSZ_W pszSource,                     // original string
  PSZ_W pszMatch,                      // found match
  SHORT sLanguageId,                   // language id to be used
  PUSHORT     pusFuzzy,                 // fuzzyness
  ULONG       ulOemCP,
  PUSHORT     pusWords,                // number of words in segment
  PUSHORT     pusDiffs                 // number of diffs in segment
);

USHORT TokenizeSource( PTMX_CLB, PTMX_SENTENCE, PSZ, PSZ, USHORT );
USHORT TokenizeSourceEx( PTMX_CLB, PTMX_SENTENCE, PSZ, PSZ, USHORT, ULONG );
USHORT TokenizeSourceEx2( PTMX_CLB, PTMX_SENTENCE, PSZ, PSZ, USHORT, ULONG, int );
USHORT TokenizeSourceEx2Ref(
   PTMX_CLB pClb,                       // pointer to control block (Null if called outside of Tm functions)
   TMX_SENTENCE& rSentence,             // pointer to sentence structure
   PSZ pTagTableName,                   // name of tag table
   PSZ pSourceLang,                     // source language
   USHORT usVersion,                    // version of TM
   ULONG  ulSrcCP,                      // OEM CP of source language     
   int iMode                            // mode to be passed to create protect table function
);

USHORT NTMMorphTokenizeW( SHORT, PSZ_W, PULONG, PVOID*, USHORT, USHORT);

USHORT NTMTokenize
(
  PVOID    pvLangCB,                   // IN : ptr to language control block
  PSZ      pszInData,                  // IN : ptr to data being tokenized
  PUSHORT  pusTermListSize,            // IN/OUT:  address of variable
                                       //    containing size of term list buffer
  PVOID    *ppTermList,                // IN/OUT: address of term list pointer
  USHORT   usListType,                 // IN: type of term list MORPH_ZTERMLIST,
                                       //    MORPH_OFFSLIST, MORPH_FLAG_OFFSLIST,
                                       //    or MORPH_FLAG_ZTERMLIST
   USHORT usVersion                    // version of TM
);

BOOL NTMTagSubst                     // generic inline tagging for TM
(
  PTMX_SUBSTPROP pSubstProp,
  ULONG          ulSrcOemCP,
  ULONG          ulTgtOemCP
);

BOOL NTMDocMatch( PSZ pszShort1, PSZ pszLong1, PSZ pszShort2, PSZ pszLong2 );

// utility to allocate pSentence and associated memory areas
USHORT NTMAllocSentenceStructure( PTMX_SENTENCE  *ppSentence );

// utility to free pSentence and associated memory areas
VOID NTMFreeSentenceStructure( PTMX_SENTENCE  pSentence );

void NTMFreeSubstProp( PTMX_SUBSTPROP pSubstProp );

USHORT  MemOpenProp( HPROP *, PVOID *, PSZ, PSZ, USHORT, BOOL );

USHORT  FillMemoryListBox ( PLISTCOMMAREA, WPARAM, LPARAM );

VOID NTMGetHandlesFromCLB ( HTM, PVOID *, PVOID * );

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*! tm.h      Internal header file for Translation Memory functions
	Copyright (c) 1990-2016, International Business Machines Corporation and others. All rights reserved.
*/
//#ifndef _EQFTMI_H_
//#define _EQFTMI_H_
/**********************************************************************/
/* This include file requires EQFDDE.H!!!                             */
/**********************************************************************/
#ifndef EQFDDE_INCLUDED
  #include "EQFDDE.H"
#endif

// include external memory export/import interface
#include "EQFMEMIE.H"

#include "tm.h"

#ifndef FIELDOFFSET
  #define FIELDOFFSET(type, field)    (LOWORD(&(((type *)0)->field)))
#endif

// file extension used for shared memory (LAN based) property files in property directory
#define LANSHARED_MEM_PROP ".SLM"


/*---------------------------------------------------------------------*\
                 #Define
\*---------------------------------------------------------------------*/

// memory export and import formats
#define MEM_SGMLFORMAT_ANSI     1
#define MEM_SGMLFORMAT_ASCII    2
#define MEM_SGMLFORMAT_UNICODE  3
#define MEM_FORMAT_TMX          4
// the same define value is used for the import as TMX (Trados) and for export as TMX (UTF-8)
#define MEM_FORMAT_TMX_UTF8     5
#define MEM_FORMAT_TMX_TRADOS   5

#define MEM_FORMAT_TMX_NOCRLF   6
#define MEM_FORMAT_TMX_UTF8_NOCRLF 7
#define MEM_FORMAT_XLIFF_MT     8


// filter for mem SGML formats (same sequence as memory export and import formats required)
//#define MEM_FORMAT_FILTERS "SGML ANSI\0*.*\0SGML ASCII\0*.*\0SGML Unicode\0*.*\0\0\0"
#define MEM_FORMAT_FILTERS "SGML ANSI\0*.*\0SGML ASCII\0*.*\0SGML UTF-16\0*.*\0TMX\0*.*\0TMX (Trados)\0*.*\0XLIFF (MT)\0*.*\0\0\0"

// filter for mem SGML formats (same sequence as memory export and import formats required)
//#define MEM_FORMAT_FILTERS_EXP "SGML ANSI\0*.*\0SGML ASCII\0*.*\0SGML Unicode\0*.*\0\0\0"
#define MEM_FORMAT_FILTERS_EXP "SGML ANSI (*.EXP)\0*.EXP\0SGML ASCII (*.EXP)\0*.EXP\0SGML UTF-16 (*.EXP)\0*.EXP\0TMX (UTF-16) (*.TMX)\0*.TMX\0TMX (UTF-8) (*.TMX)\0*.TMX\0TMX (UTF-16) (remove CRLF) (*.TMX)\0*.TMX\0TMX (UTF-8) (remove CRLF) (*.TMX)\0*.TMX\0\0\0"

// defines for retries in case of BTREE_IN_USE conditions
#define MAX_RETRY_COUNT 30
#define MAX_WAIT_TIME   100

#define TMT_CODE_VERSION    5            // Code version
#define TM_PREFIX          "EQFTMT$$"     // TM DB identifier
#define HUNDRED           100          //
// ID to be used if a table overflow occurs
#define OVERFLOW_ID       32000
// name to be used if a table overflow occurs
#define OVERFLOW_NAME     "$$$$$$$$"

#define LAST_CLUSTER_NUMBER  4095

//--- size of the message buffer for the Error message               /*@1108A*/
//--- ERROR_MEM_SEGMENT_TOO_LARGE_CON                                /*@1108A*/
#define MSG_BUFFER 35                                                /*@1108A*/


#define MIN_SPOOL_SIZE      20480  // 20k bytes for preformatted TM blocks
#define SECTOR_SIZE          4096  // Disk sector. Fixed now, dynamic later
#define BLOCK_HEADER_SIZE       8  // size of block header
#define MAX_TM_HEADER_SIZE  47600  // max size of TM header
#define MAX_BLOCK_SIZE       4096  // Maximum block size
#define MAX_TEXT_TAB_SIZE (MAX_TAGS_TAB_ENTRIES * sizeof(TOKENENTRY))
#define MAX_WORDS_TAB_SIZE (MAX_WORDS_TAB_ENTRIES * sizeof(TOKENENTRY))

#define MAX_TM_WORK_AREA  ( MAX_TGT_LENGTH + 300 )
                               /* Work areas to convert LF into CRFL   */
                               /* and the other way round              */

// The following define should not exceed 65535 Bytes
#define MAX_TMT_GLOBALS_SIZE (sizeof(TMT_GLOBALS) +\
                             MAX_TM_HEADER_SIZE +\
                             MAX_BLOCK_SIZE+\
                             MAX_TEXT_TAB_SIZE+\
                             MAX_WORDS_TAB_SIZE)


#define MAX_WORDS_TAB_ENTRIES  200 /* Number of entries in WordsTable  */
#define MAX_TAGS_TAB_ENTRIES   100 /* number of entries in TextTable   */
#define KEY_DIR_ENTRIES_NUM   4096 /* number of entries key directory  */

#define TOP_BLOCK_NUMBER (USHORT)65535
                               /* 2**16 - 1, the max number of a block */
#define MAX_BLOCKS_NUM   (USHORT)65535
                               /* 2**16 - 1, maximal number of blocks  */
#define GROUP_NUM           8  /* number of distribution groups        */

#define  TAG_STARTING_VALUE 0  /* the lowest attribute to tags in text */
                               /* table                                */
#ifndef  TM_ADM
#define MAX_SERVER_NAME    15  /* length of server name                */
#endif

/* The two defines below should not be used. Displacement can be       */
/* computed in runtime from the structure.                             */
#define SEG_LENGTH_DISP     5  /* disp of length field in a SEGMENT    */
#define DEL_FLAG_DISP       6  /* disp of del flag from segment start  */

// data compress flag
#define   BOCU_COMPRESS  0x01


/* define for write Tm Header function                                 */
#define WF_ALL            0x0000  /* Write the whole header............*/
#define WF_CORRUPT        0x0001
#define WF_TMBLOCKS       0x0002
#define WF_FREEBLOCKS     0x0004
#define WF_FIRSTAVAIL     0x0008
#define WF_UPDATE         0x4000  /* Write all but the key directory...*/
#define WF_KEYDIR         0x8000  /* Write the key directory...........*/


/*---------------------------------------------------------------------*\
  match type definitions
\*---------------------------------------------------------------------*/
#define USE_CRLF       1
#define ALIGN_CRLF     2
#define IGNORE_CRLF    3

/* return codes for the Tmt Commands                                   */
#define OK                  NO_ERROR    /* for Tmt commands            */



/*----------------------------------------------------------------------------*\
  System wide lengthes for correction of the thresholds in dependency
  of the length of the input segment
\*----------------------------------------------------------------------------*/
//@@@                           // segments, defined thru LENGTH_SHORTER_VALUE
#define LENGTH_SHORTER_VALUE   2      // Length for shorter segment
//@@@                           // segments, defined thru LENGTH_SHORTER_VALUE
#define LENGTH_SHORT_VALUE     6      // Length for short segment
#define LENGTH_MEDIUM_VALUE   10      // Length for medium segment
#define LENGTH_LONG_VALUE     20      // Length for long segment

/*----------------------------------------------------------------------------*\
  System wide percentages for correction of the MATCH threshold
\*----------------------------------------------------------------------------*/
#define MATCH_PERCENTAGE_SHORT_VALUE    1L     // percentage for short segment
#define MATCH_PERCENTAGE_MEDIUM_VALUE  10L     // percentage for medium segment
#define MATCH_PERCENTAGE_LONG_VALUE    20L     // percentage for long segment
#define MATCH_PERCENTAGE_LONGER_VALUE  40L     // percentage for longer segment

/*----------------------------------------------------------------------------*\
  System wide percentages for correction of the LENGTH threshold
\*----------------------------------------------------------------------------*/
#define LENGTH_PERCENTAGE_SHORT_VALUE    1L     // percentage for short segment
#define LENGTH_PERCENTAGE_MEDIUM_VALUE  10L     // percentage for medium segment
#define LENGTH_PERCENTAGE_LONG_VALUE    20L     // percentage for long segment
#define LENGTH_PERCENTAGE_LONGER_VALUE  30L     // percentage for longer segment

/*---------------------------------------------------------------------*\
                            Macro Definition
\*---------------------------------------------------------------------*/
#define FPTR(type, field) ((ULONG)(FIELDOFFSET(type, field)))

/**********************************************************************/
/* macro to build index name from fully qualified data name           */
/**********************************************************************/
#define INDEXNAMEFROMMEMPATH( mem, ind ) \
  { \
  Utlstrccpy( ind, mem, DOT ); \
  if ( strcmp( strrchr( mem, DOT ), EXT_OF_SHARED_MEM ) == 0 ) \
    strcat( ind, EXT_OF_SHARED_MEMINDEX ); \
  else \
    strcat( ind, EXT_OF_TMINDEX ); \
  }

  // replace any 0xA0 in language name to 0xFF
  // (0xA0 is 0xFF after processing by OemToAnsi)
  #define REPLACE_A0_BY_FF( p ) \
  {                          \
    PBYTE pbTemp = (PBYTE)p; \
    while ( *pbTemp )        \
    {                        \
      if ( *pbTemp == 0xA0 ) \
      {                      \
        *pbTemp = 0xFF;      \
      }                      \
      pbTemp++;              \
    }                        \
  }

#include "EQFTAG.H"
/*---------------------------------------------------------------------*\
                 Typedefs Definition
+-----------------------------------------------------------------------+
  Variable prefixes:
  USHORT id, num, len, disp
  ULONG  ldisp
  CHAR   buf[]
\*---------------------------------------------------------------------*/


typedef struct _TM_HEADER_UPDATE { /* tmhu */
   BOOL    fCorruption ;
   USHORT  usNumTMBlocks,    /* number of blocks in the TM             */
           usNumFreeBlocks,  /* # of free, pre-formatted blocks        */
           usFirstAvailBlock;/* points to first available block        */
} TM_HEADER_UPDATE;

typedef union  _UNIONIN
{
   PREFIX_IN         in;
   ADD_IN            ain;
   DEL_IN            din;
   REP_IN            rin;
   EXT_IN            ein;
   GET_IN            gin;
   CLOSE_IN          clin;
   OPEN_IN           oin;
   CREATE_IN         crin;
   INFO_IN           infoin;
   CLOSEHANDLER_IN   chin;
   EXIT_IN           xin;
   DRIVES_IN         drivesin;
   FILE_LIST_IN      filelistin; // !!! CHM
   GETPART_IN        getpartin;
   PUTPROP_IN        putpropin;
   PUTDICTPROP_IN    PutDictPropIn; // !!! CHM added
   PUTPROPCOMBINED_IN PutPropCombinedIn; // !!! CHM added
   GETPROP_IN        getpropin;
   ENDORG_IN         endorgin;
   DELTM_IN          deltmin;
   DELFILE_IN        delfilein;
   FILEINFO_IN       fileinfoin;
   RENFILE_IN        renfilein;
} UNIONIN, * PUNIONIN; /* uin */

typedef union  _UNIONOUT
{
   PREFIX_OUT  out;
   ADD_OUT     aout;
   DEL_OUT     dout;
   REP_OUT     rout;
   EXT_OUT     eout;
   GET_OUT     gout;
   CLOSE_OUT   clout;
   OPEN_OUT    oout;
   CREATE_OUT  crout;
   INFO_OUT    infoout;
   EXIT_OUT    xout;
   DRIVES_OUT    drivesout;
   FILE_LIST_OUT filelistout; // !!! CHM
   GETPART_OUT   getpartout;
   PUTPROP_OUT   putpropout;
   GETPROP_OUT   getpropout;
   GETDICTPROP_OUT      GetDictPropOut; // !!! CHM added
   GETPROPCOMBINED_OUT  GetPropCombinedOut; // !!! CHM added
   ENDORG_OUT    endorgout;
   DELTM_OUT     deltmout;
   DELFILE_OUT   delfileout;
   FILEINFO_OUT  fileinfoout;
   RENFILE_OUT   renfileout;
} UNIONOUT, * PUNIONOUT; /* uout */

/*
 +---------------------------------------------------------------------------+
    Name:         fTmComInit
    Purpose:      Initialise the TM Communication code (U code)
    Parameters:   1.VOID   - nothing
    Returns:      BOOL - TRUE -> initialization completed successfully
                         FALSE -> initialization ended with an error
    Comments:     This procedure initalizes the TM Communication code (U
                  code). At the moment this only resets the top pointer of
                  the TM Handle information list.
    Samples:      fRc = fTmComInit ();
 +---------------------------------------------------------------------------+
*/
BOOL fTmComInit (VOID);

VOID   QDAMDeleteFileRemote( PDELFILE_IN  pDelFileIn,      // Input structure
                             PDELFILE_OUT pDelFileOut );   // Output structure


typedef struct _TMT_GLOBALS { /* tmtg */
 /* this structure keeps data and pointers to variables that exist from*/
 /* the point that the TM was created or opened, until close command   */
 /* BlockImage, TextTable, WordsTable and TmHeader are allocated       */
 /* dynamically during Create/Open  and are freed at Close time.       */
  HFILE    hfTM;                  /* handle to TM db (from Dos call)   */
  PUCHAR   pchBlockImage;         /* pointer to block image            */
  PTOKENENTRY pteTextTable,       /* pointer to TextTable              */
              pteWordsTable,      /* pointer to WordsTable             */
              pteFirstSigWord,    /* pointer to first significant word */
              pteSecondSigWord;   /* pointer to second significant word*/
  PPREFIX_OUT pPrefixOut;         /* pointer to the current PrefixOut  */
                                  /* to be used by FormatMore          */
  SEGMENT     seg;                /* placed here instead of allocating */
                                  /* this space on stack (point 276)   */
  MATCH       mtch;               /* placed here instead of allocating */
                                  /* this space on stack (point 276)   */
  PCHAR       pWorkArea1;         /* Pointer to work area 1            */
  PCHAR       pWorkArea2;         /* Pointer to work area 2            */
  PTM_HEADER  pTmHeader;          /* pointer to Tm header structure    */
  LONG        lActLengthThr;      /* length corrected length threshold values*/
  LONG        lActMatchThr;       /* length corrected match threshold values */
  PLOADEDTABLE pLoadedTagTable;   /* pointer to loaded tagtable        */
  PVOID        pstLoadedTagTable; /* pointer to loaded tagtable, used for */
                                  /* function TATagTokenize           */
} TMT_GLOBALS, * PTMT_GLOBALS, ** PPTMT_GLOBALS;

// ***************** Work Constants global **************************
#define  INIT_NUMB_OF_ENTRIES     5   // Initial number of entries in a table or List
#define  SEG_NUMB                 6   // Segment number in char.
#define  ASCII_FLAG               1   // Ascii flag converted to char.
#define  MACH_TRANS               1   // Machine trans.flag converted to char.
#define  TIME_STAMP              16   // Time integer converted to character
#define  IND_CODES               20   // External industry codes space to hold a maximum of 6 codes
#define  ASCII_IND_CODES_LENGTH   3   // Length of Industry codes in external format
#define  NUMB_OF_IND_CODES        6   // Number of Industry codes in external format
#define  MEM_NAME                 8   // Length of memory database name without extension
#define  DRIVE_NAME              12   // Special drive name
#define  PTR_MEMHANDLER_IDA       0   // Relative position in the extra bytes for handler
#define  PTR_MEM_IDA              0   // Relative position in the extra bytes for instance
#define  PTR_CRT_IDA              0   // Relative position in the extra bytes for create dialog
#define  PTR_DLG_IDA              0   // Relative position in the extra bytes for dialogs
#define  TEMP                    40   // Size of temporaty work area
                                      // of WinRegisterClass call.
#define  TEXT_LINE_LENGTH             40  // Text line length
#define  TEXT_100_CHAR               100  // string length for temporary strings
//#define  NUMB_OF_TOKENS             1000  // Number of tokens in the token list
#define  NUMB_OF_TOKENS             8000  // Number of tokens in the toklist:RJ increase nec.
                                          // if 65520 bytes are read-in at once during MemImport
#define  MEM_PROP_SIZE              2048  // Global size of all memory database properties
#define  MEM_BLOCK_SIZE             1024  // Translation Memory block size
#define  SEGMENT_CLUSTER_LENGTH        4  // Length of segment cluster
#define  SEGMENT_NUMBER_LENGTH         6  // Length of segment number
#define  PROCESS_NUMB_OF_MESSAGES     10  // Number of messages to be process till next message is issued
#define  MEM_DBCS                      0  // 0 = No support,    1 = DBCS support
#define  MEM_LOAD_PATTERN_NAME        "*" // Default names to be shown for load dialog
#define  MEM_LOAD_PATTERN_EXT        ".*" // Default extension to be shown for load dialog
#define  MEM_EXPORT_WORK_AREA       6000  // Length of export work area
#define  EQF_IDENTIFICATION         "EQF" // EQF identification
#define  CLBCOL_TITLE_STRING        "                   " // Placeholder for of CLBCOL titles
#define  MEM_EXPORT_OUT_BUFFER      8200  // Output buffer for export



// *****************  Memory database load **************************
//#define  MEM_CONTEXT_TOKEN_END     0     // </Context>
//#define  MEM_CONTROL_TOKEN_END     1     // </Control> UNUSED!
//#define  NTM_DESCRIPTION_TOKEN_END 2     // </Description>
//#define  MEM_MEMORYDB_TOKEN_END    3     // </MemoryDb>
//#define  NTM_MEMORYDB_TOKEN_END    4     // </NTMMemoryDb>
//#define  MEM_SEGMENT_TOKEN_END     5     // </Segment>
//#define  MEM_SOURCE_TOKEN_END      6     // </Source>
//#define  MEM_TARGET_TOKEN_END      7     // </Target>
//#define  MEM_CONTEXT_TOKEN         8     // <Context>
//#define  MEM_CONTROL_TOKEN         9     // <Control>
//#define  NTM_DESCRIPTION_TOKEN    10     // <Description>
//#define  MEM_MEMORYDB_TOKEN       11     // <MemoryDb>
//#define  NTM_MEMORYDB_TOKEN       12     // <NTMMemoryDb>
//#define  MEM_SEGMENT_TOKEN        13     // <Segment>
//#define  MEM_SOURCE_TOKEN         14     // <Source>
//#define  MEM_TARGET_TOKEN         15     // <Target>

// strings to create the token IDs for the tags dynamically using TATagTokenize
#define  MEM_CONTEXT_TOKEN_END     L"</Context>"
#define  MEM_CONTROL_TOKEN_END     L"</Control>"
#define  NTM_DESCRIPTION_TOKEN_END L"</Description>"
#define  MEM_MEMORYDB_TOKEN_END    L"</MemoryDb>"
#define  NTM_MEMORYDB_TOKEN_END    L"</NTMMemoryDb>"
#define  MEM_SEGMENT_TOKEN_END     L"</Segment>"
#define  MEM_SOURCE_TOKEN_END      L"</Source>"
#define  MEM_TARGET_TOKEN_END      L"</Target>"
#define  MEM_CONTEXT_TOKEN         L"<Context>"
#define  MEM_CONTROL_TOKEN         L"<Control>"
#define  NTM_DESCRIPTION_TOKEN     L"<Description>"
#define  MEM_MEMORYDB_TOKEN        L"<MemoryDb>"
#define  NTM_MEMORYDB_TOKEN        L"<NTMMemoryDb>"
#define  MEM_SEGMENT_TOKEN         L"<Segment>"
#define  MEM_SOURCE_TOKEN          L"<Source>"
#define  MEM_TARGET_TOKEN          L"<Target>"
#define  MEM_CODEPAGE_TOKEN        L"<CodePage>"
#define  MEM_CODEPAGE_TOKEN_END    L"</CodePage>"
#define  MEM_ADDDATA_TOKEN_END     L"</AddData>"
#define  MEM_ADDDATA_TOKEN         L"<AddData>"




#define  TM_IMPORT_OK              0     // Translation memory import OK
#define  TM_IMPORT_FAILED          1     // Translation memory import failed
#define  TM_IMPORT_FORCED          2     // Translation memory import was forced


//used for input from create folder dialog
typedef enum
{
  MEM_CREATE_NAME_IND,
  MEM_CREATE_MARKUP_IND,
  MEM_CREATE_SOURCELANG_IND,
  MEM_CREATE_TARGETLANG_IND
} MEM_CREATEINDEX;

#define  MEM_TEXT_BUFFER         65520     // Length of the text buffer


// ************ Definitions for TM list box display *********************
typedef enum
{
  MEM_OBJECT_IND,
  MEM_NAME_IND,
  MEM_DESCRIPTION_IND,
  MEM_SIZE_IND,
  MEM_DRIVE_IND,
  MEM_SERVER_IND,
  MEM_OWNER_IND,
  MEM_SOURCELNG_IND,
  MEM_TARGETLNG_IND,
  MEM_MARKUP_IND
} MEM_ITEMINDX;

/**********************************************************************/
/* string IDs to parse the CONTROL string of the TM exported format   */
/* using UtlParseX15                                                  */
/**********************************************************************/
//#define NTM_SEGNR_ID          0   //seg nr from analysis
//#define NTM_MTFLAG_ID         1   //machine translation flag
//#define NTM_TIME_ID           2   //time stamp
//#define NTM_SOURCELNG_ID      3   //source language
//#define NTM_TARGETLNG_ID      4   //target language
//#define NTM_AUTHORNAME_ID     5   //author name
//#define NTM_TAGTABLENAME_ID   6   //tag table name
//#define NTM_FILENAME_ID       7        //file name

typedef enum
{
  NTM_SEGNR_ID,
  NTM_MTFLAG_ID,
  NTM_TIME_ID,
  NTM_SOURCELANG_ID,
  NTM_TARGETLANG_ID,
  NTM_AUTHORNAME_ID,
  NTM_TAGTABLENAME_ID,
  NTM_FILENAME_ID,
  NTM_LONGNAME_ID
} NTM_IMPORTINDEX;

#define START_KEY             0xFFFFFF

#define EXT_OF_RENAMED_TMDATA  ".TRD"
#define EXT_OF_RENAMED_TMINDEX ".TRI"
#define EXT_OF_TEMP_TMPROP     ".TMR"
#define EXT_OF_RENAMED_TMPROP  ".RMR"
#define EXT_OF_TEMP_TMDATA     ".TTD"
#define EXT_OF_TEMP_TMINDEX    ".TTI"
#define EXT_OF_TMPROP          EXT_OF_MEM


// ************ Type definitions ****************************************

typedef struct _SEG_CTRL_DATA
{
 CHAR     chSegmentNumber[SEG_NUMB];  /* Segment number converted to character*/
 CHAR     chAsciiFlag[ASCII_FLAG];    /* Ascii flag converted to char.        */
 CHAR     chMachineTrans[MACH_TRANS]; /* Machine trans.flag converted to char.*/
 CHAR     chTimeStamp[TIME_STAMP];    /* Time integer converted to character  */
 CHAR     chIndustryCodes[IND_CODES]; /* Industry codes                       */
 CHAR     chFileName[MAX_FILESPEC-1]; /* Segment origin. from that file name  */
}SEG_CTRL_DATA, * PSEG_CTRL_DATA;


typedef struct _MEM_PROC_HANDLE
{
 CHAR   * pDataArea;                   /* Pointer to process data area        */
 USHORT   usMessage;                   /* Termination message for process     */
}MEM_PROC_HANDLE, * PMEM_PROC_HANDLE;

typedef struct _MEM_IDA
{
 IDA_HEAD stIdaHead;                     // Standard Ida head
 HWND     hWndListBox;                   // Handle of memory window listbox
 SHORT    sLastUsedViewList[MAX_VIEW];   // last used view list
 SHORT    sDetailsViewList[MAX_VIEW];    // user's details view list'
 SHORT    sSortList[MAX_VIEW];           // user's sort criteria list'
 HWND     hWnd;                          // Handle of memory window
 CHAR     szTemp[4096];                  // Temporary work area
 CHAR     szTempPath[MAX_EQF_PATH];      // Temporary work area for a path
 CHAR     szMemPath[4096];               // Full path to TM starting an operation
 CHAR     szMemName[MAX_LONGFILESPEC];   // (long) TM name
 CHAR     szMemObjName[2*MAX_LONGFILESPEC];   // memory object name ( pluginname + ":" + (long) TM name)
 CHAR     szPluginName[MAX_LONGFILESPEC]; // name of plugin for this memory
 LONG     lTemp;                         // Temporary long field
 CHAR     szMemFullPath[MAX_EQF_PATH];   // Full path to memory database
 CHAR     szSecondaryDrives[MAX_DRIVELIST]; // Drives of secondary installations
 CHAR   * pWorkPointerLoad;                 // A work pointer for the load proc.
// SHORT    sNumberOfMem;                     // Number of memory databases entries available
// SHORT    sNumberOfMemUsed;                 // Number of memory databases entries used
 PMEM_PROC_HANDLE  pMemProcHandles;         // pointer to List of proc. handle
 SHORT    sNumberOfProc;                    // Number of process handle entries
 SHORT    sNumberOfProcUsed;                // Number of proc. handle entries used
 SHORT    sRunningProcesses;                // Number of concurrently running processes
 CHAR     szText[TEXT_LINE_LENGTH];         // Containing text
// CHAR     szMemTopItem[MAX_FNAME +          // In case of refresh contains top item of listbox
//                       MAX_DESCRIPTION + 5];// the 5 additional char's are for \x15 control characters
// CHAR     szMemSelectedItem[MAX_FNAME +     // In case of refresh contains selected item of listbox
//                       MAX_DESCRIPTION + 5];// the 5 additional char's are for \x15 control characters
 CHAR     szProcessTaskWithObject[MAX_FILESPEC]; // A Task has to be processed with this Object
 CHAR     szNAString[TEXT_LINE_LENGTH];     // String to store the "N/A" string
}MEM_IDA, * PMEM_IDA;


class OtmMemory;
class OtmProposal;

//#ifdef _OTMMEMORY_H_
typedef struct _MEM_LOAD_IDA
{
 CHAR         szMemName[MAX_LONGFILESPEC];    // Memory database name
 CHAR         szShortMemName[MAX_FILESPEC];   // Memory database name
 CHAR         szMemPath[2048];                // Full memory database name + path
 CHAR         szFilePath[2048];               // Full file name + path
 BOOL         fControlFound;                  // Indicator whether a CONTROL token was found
 OtmMemory    *pMem;                          // pointer to memory object
 OtmProposal  *pProposal;                     // buffer for memory proposal data
 CHAR_W       szSegBuffer[MAX_SEGMENT_SIZE+1];// buffer for segment data
 CHAR_W       szSource[MAX_SEGMENT_SIZE+1];   // buffer for segment source data
 HFILE        hFile;                          // Handle of file to be loaded
 HWND         hProgressWindow;                // Handle of progress indicator window
 ULONG        ulProgressPos;                  // position of progress indicator
 ULONG        ulBytesRead;                    // bytes already read from the import file
 ULONG        ulTotalSize;                    // total size of import file
 BOOL         fFirstRead;                     // Read Flag
 PLOADEDTABLE pFormatTable;                   // Pointer to Format Table
 PTOKENENTRY  pTokenList;                     // Pointer to Token List
 BOOL         fEOF;                           // Indicates end of file
 PTOKENENTRY  pTokenEntry;                    // A pointer to token entries
 PTOKENENTRY  pTokenEntryWork;                // A work pointer to token entries
 ULONG        ulSegmentCounter;               // Segment counter of progress window
 ULONG        ulInvSegmentCounter;            // Invalid Segment counter
 ULONG        ulProgress;
 ULONG        ulInvSymbolsErrors;
 ULONG        ulResetSegmentCounter;          // Segments using generic markup when not valid
 CHAR         szSegmentID[SEGMENT_CLUSTER_LENGTH +
                          SEGMENT_NUMBER_LENGTH + 2]; // Segment identification
 CHAR         szFullFtabPath[MAX_EQF_PATH];   // Full path to tag tables
 CHAR_W       szTextBuffer[MEM_TEXT_BUFFER];  // Text buffer to keep the file
 PMEM_IDA     pIDA;                           // Address to the memory database IDA
 BOOL         fDisplayNotReplacedMessage;     // message flag if segment not /*@47A*/
                                              // not replaced message should /*@47A*/
                                              // be displayed or not         /*@47A*/
 CHAR         szTargetLang[MAX_LANG_LENGTH];
 CHAR         szTagTable[MAX_FNAME];
 BOOL         fTagLangDlgCanceled;
 USHORT       usTmVersion;
 BOOL         fBatch;                         // TRUE = we are in batch mode
 HWND         hwndErrMsg;                     // parent handle for error messages
 PDDEMEMIMP   pDDEMemImp;                     // ptr to batch memory import data
 HWND         hwndNotify;                 // send notification about completion
 OBJNAME      szObjName;                  // name of object to be finished
 CHAR         szDescription[MAX_MEM_DESCRIPTION];   //description of memory database
 CHAR         szTempPath[MAX_PATH144];        // buffer for path names
 USHORT       usImpMode;                  // mode for import
 BOOL         fMerge;                     // TRUE = TM is being merged
 PSZ          pszList;                    // list of imported files or NULL
 PSZ          pszActFile;                 // ptr to active file or NULL
 ULONG        ulFilled;                   // filled during read (in num CHAR_Ws)
 BOOL         fSkipInvalidSegments;       // TRUE = skip invalid segments w/o notice
 ULONG        ulOemCP;                    // CP of system preferences lang.
 ULONG        ulAnsiCP;                   // CP of system preferences lang.
 BOOL         fIgnoreEqualSegments;       // TRUE = ignore segments with identical source and target string
 BOOL         fAdjustTrailingWhitespace;  // TRUE = adjust trailing whitespace of target string

 // dynamically evaluated token IDs
 SHORT sContextEndTokenID;
 SHORT sControlEndTokenID;
 SHORT sDescriptionEndTokenID;
 SHORT sMemMemoryDBEndTokenID;
 SHORT sNTMMemoryDBEndTokenID;
 SHORT sSegmentEndTokenID;
 SHORT sSourceEndTokenID;
 SHORT sTargetEndTokenID;
 SHORT sContextTokenID;
 SHORT sControlTokenID;
 SHORT sDescriptionTokenID;
 SHORT sMemMemoryDBTokenID;
 SHORT sNTMMemoryDBTokenID;
 SHORT sSegmentTokenID;
 SHORT sSourceTokenID;
 SHORT sTargetTokenID;
 SHORT sCodePageTokenID;
 SHORT sCodePageEndTokenID;
 SHORT sAddInfoEndTokenID;
 SHORT sAddInfoTokenID;

 // fields for external memory import methods
 //HMODULE       hmodMemExtImport;                 // handle of external import module/DLL
 PMEMEXPIMPINFO pstMemInfo;                        // buffer for memory information
 PMEMEXPIMPSEG  pstSegment;                        // buffer for segment data

 LONG          lExternalImportHandle;            // handle of external memory import functions

 BOOL         fMTReceiveCounting;         // TRUE = count received words and write counts to folder properties
 OBJNAME      szFolObjName;               // object name of folder (only set with fMTReceiveCounting = TRUE)
 ULONG        ulMTReceivedWords[3];       // received words per category
 ULONG        ulMTReceivedSegs[3];        // received segments per category
 LONG         lProgress;                  // progress indicator of external import methods
 BOOL         fYesToAll;                  // yes-to-all flag for merge confirmation
 BOOL          fForceNewMatchID;          // create a new match segment ID even when the match already has one
 BOOL          fCreateMatchID;            // create match segment IDs
 CHAR          szMatchIDPrefix[256];      // prefix to be used for the match segment ID
 CHAR_W        szMatchIDPrefixW[256];     // prefix to be used for the match segment ID (UTF16 version)
 CHAR_W        szMatchSegIdInfo[512];     // buffer for the complete match segment ID entry
 ULONG         ulSequenceNumber;          // segment sequence number within current external memory file
}MEM_LOAD_IDA, * PMEM_LOAD_IDA;

typedef struct _MEM_MERGE_IDA
{
 CHAR          szPathMergeMem[MAX_LONGPATH];  // Full path and name of TM to be merged
 CHAR          szPathMergeProp[MAX_LONGPATH]; // Full path and name of Properties to be imported
 CHAR          szDriveMergeMem[MAX_DRIVE];    // Drive letter of TM to be merged w o : ( d )
 CHAR          szNameMergeMem[MAX_LONGFILESPEC];// Name of TM to be merged w o ext ( heller )
 CHAR          szShortNameMergeMem[MAX_FILESPEC];// Short name of TM being merged
 CHAR          szDirMergeMem[MAX_LONGPATH];   // Path of directories fo TM to be merged ( \eqf\import\ )
 CHAR          szExtMergeMem[MAX_FEXT];       // Ext of TM to be merged ( MIP or MEM or ? )
 OtmMemory     *pMergeMem;                     // TM handle of TM to be merged
 CHAR          szInvokingHandler[40];         // ??? 40 ???? to be in Gerds stuff. Name of handler which invoked the process
 CHAR          szSystemPath[MAX_EQF_PATH];    // Path to the EQF system
 CHAR          szTemp[MAX_EQF_PATH];          // Temporary path area
 CHAR          szPropName[MAX_FILESPEC];      // TM property name ( xxxx.MEM )
 CHAR          szPathMem[MAX_LONGPATH];       // Full name and Path to the TM ( c:\EQF\MEM\xxxx.MEM )
 CHAR          szPathProp[MAX_LONGPATH];      // Full name and Path to the Properties
 CHAR          szDriveMem[MAX_DRIVE];         // Drive letter of TM w o : ( h )
 CHAR          szNameMem[MAX_LONGFILESPEC];   // Long name of TM w o ext ( gallus )
 CHAR          szShortNameMem[MAX_FILESPEC];  // Short name of TM w o ext ( gallus )
 OtmMemory     *pOutputMem;                   // TM handle
 BOOL          fPropExist;                    // Existence of properties 0=No 1=Yes
 BOOL          fPropCreated;                  // Tm properties have been created
 BOOL          fMsg;                          // A message has been issued already
 BOOL          fImport;                       // If set the merge is started via an import
 USHORT        usImportRc;                    // Import function return code
 ULONG         ulSegmentCounter;              // Number of segments merged
 ULONG         ulInvSegmentCounter;           // Invalid Segment counter
 EXT_IN        stOldExtIn;                    // input for TmOldExtract
 EXT_OUT       stOldExtOut;                   // output for TmOldExtract
 TMX_EXT_IN_W  stExtIn;                       // TMX_EXTRACT_IN structure
 TMX_EXT_OUT_W stExtOut;                      // TMX_EXTRACT_OUT structure
 TMX_PUT_IN_W  stPutIn;                       // TMX_PUT_IN structure
 TMX_PUT_OUT_W stPutOut;                      // TMX_PUT_OUT structure
 TIME_L        tStamp;                        // Time stamp of merge start time
 HWND          hwndMemLb;                     // Handle to the TM listbox
 HWND          hProgressWindow;               // Handle of progress indicator window
 ULONG         ulProgressPos;                 // position of progress indicator
 CHAR          szServer[MAX_LONGPATH];        // Server Name of TM or \0 if TM is local
 BOOL          fPropReceived;                 // Property file got via Receive ?
 BOOL          fOrganizeInvoked;              // TRUE if Organize is invoked
 BOOL          fImportAnyway;                 // FALSE if import of TM with
                                              // different IDs is canceled
 CHAR          szSourceMemSourceLang[MAX_LANG_LENGTH];
 CHAR          szSourceMemTargetLang[MAX_LANG_LENGTH];
 CHAR          szSourceMemMarkup[MAX_FNAME];                         /*@1276A*/
 CHAR          szTargetMemSourceLang[MAX_LANG_LENGTH];
 CHAR          szTargetMemTargetLang[MAX_LANG_LENGTH];
 CHAR          szTargetMemMarkup[MAX_FNAME];                         /*@1276A*/
 BOOL          fDisplayMsg;             // message flag if segment not /*@47A*/
                                        // not replaced message should /*@47A*/
                                        // be displayed or not         /*@47A*/
 BOOL          fOldPropFile;                  // used for folder import
 CHAR          szTagTable[MAX_FILESPEC];      // tag table of org TM
 CHAR          szPathMergeIndex[MAX_LONGPATH];// Full path and name of index to be merged
 CHAR          szPathIndex[MAX_LONGPATH]; // name and path to index C:\EQF\MEM\xxxx.TMI )
 BOOL         fBatch;                     // TRUE = we are in batch mode
 HWND         hwndErrMsg;                 // parent handle for error messages
 PDDEMEMEXP   pDDEMemExp;                 // ptr to batch memory export data
 CHAR         szLongName[MAX_LONGFILESPEC]; // buffer for long TM names
 USHORT       usTask;                      // current taskl to do (batch mode)
 OtmProposal  *pProposal;                   // buffer for proposal data
 BOOL         fFirstExtract;                // TRUE = this ist the first extract call
 int          iComplete;                    // process completion rate
}MEM_MERGE_IDA, * PMEM_MERGE_IDA;

/**********************************************************************/
/* Dialog IDA for TM property dialog                                  */
/**********************************************************************/
typedef struct _MEM_PROP_IDA
{
 CHAR         szMemName[MAX_LONGFILESPEC];// Memory database name without extension
 OtmMemory    *pMem;                       // Handle of memory database
 HPROP        hPropMem;                   // Memory database property handle
 PPROP_NTM    pPropMem;                   // pointer to TM properties
 CHAR         szPropName[MAX_FILESPEC];   // buffer for property name
 CHAR         szPropPath[MAX_EQF_PATH];   // buffer for property path
 CHAR         szTempPath[MAX_EQF_PATH];   // buffer for path names
}MEM_PROP_IDA, * PMEM_PROP_IDA;


BOOL EqfMemPropsToHtml( HWND hwndParent, PMEM_IDA  pIDA, OtmMemory *pMem );

VOID    EQFMemImportTrojaEnd( PMEM_MERGE_IDA );
USHORT  CloseMergeTmAndTm( PMEM_MERGE_IDA, BOOL );                   /*@1139A*/
USHORT MemFuncMergeTM
(
  PMEM_MERGE_IDA    pMIDA           // Pointer to the merge IDA
);

//#endif

typedef struct _MEMORY_HANDLER_DATA
{
 IDA_HEAD  stIdaHead;                    // Standard Ida head
}MEMORY_HANDLER_DATA, * PMEMORY_HANDLER_DATA;


/**********************************************************************/
/* TMX_ENDORG_IN, TMX_ENDORG_OUT used by NTMCloseOrganize             */
/* Structures needed for the TMC_END_ORGANIZE command which is used   */
/* to end an 'Organize' process.                                      */
/* This command is sent to the original TM instead                    */
/* of the TM_CLOSE command and handles the closing, deletion and      */
/* renaming of the original and temporary TM file and index.          */
/* The temporary file has to be closed previously.                    */
/**********************************************************************/
typedef struct _TMX_ENDORG_IN
{
  TMX_PREFIX_IN  stPrefixIn;
  CHAR           szOrgTM[MAX_EQF_PATH];           //full name of original TM
  CHAR           szTmpTM[MAX_EQF_PATH];           //full name of temporary TM
  CHAR           szOrgIndex[MAX_EQF_PATH];        //full name of original index file
  CHAR           szTmpIndex[MAX_EQF_PATH];        //full name of temporary index file
  CHAR           szOrgProp[MAX_EQF_PATH];         //full name of original property file
  CHAR           szTmpProp[MAX_EQF_PATH];         //full name of temporary property file
  USHORT         usOrgType;                       //type ORGANIZE, CONVERT
} TMX_ENDORG_IN, * PTMX_ENDORG_IN;

typedef struct _TMX_ENDORG_OUT
{
  TMX_PREFIX_OUT  stPrefixOut;
} TMX_ENDORG_OUT, * PTMX_ENDORG_OUT;

/**********************************************************************/
/* The following structures for dialog IDAs are defined only          */
/* if INCL_EQFMEM_DLGIDAS has been defined                            */
/**********************************************************************/
#if defined(INCL_EQFMEM_DLGIDAS)

typedef struct _MEM_INCL_DLG_IDA
{
 BOOL         fInitErrorOccurred;         // Important init error occurred
}MEM_INCL_DLG_IDA, * PMEM_INCL_DLG_IDA;

#endif

// Structure of EQF memory properties
struct memlst_prop
{
   PROPHEAD  PropHead;                   // Common header of properties
   EQF_SWP   Swp;                        // Window position
   BYTE   szDriveList[27];               // List of drive letters
   USHORT usViewFormat;                  // VIEW format
   SHORT  sLastUsedViewList[MAX_VIEW];   // last used view list
   SHORT  sDetailsViewList[MAX_VIEW];    // user's details view list'
   SHORT  sSortList[MAX_VIEW];           // user's sort criteria list'
   CLBFILTER Filter;                     // currently active column listbox filter
   SHORT  sLastUsedViewWidth[MAX_VIEW];   // last used view list
};
typedef struct memlst_prop PROPMEMORY, *PPROPMEMORY;

typedef struct _SLIDER_DATA
{
   CHAR szLine [5] [TEXT_100_CHAR+MAX_PATH144]; // 5 text lines of 100 characters
                                             // + max path length
} SLIDER_DATA, * PSLIDER_DATA;



/*--------------------------------------------------------------------------*\
     Function prototypes.
\*--------------------------------------------------------------------------*/
USHORT
  OpenTmFile (PTMT_GLOBALS ptmtg,      /*.The TM Globals Area.............*/
              PSZ          pszFileName,/*.The TM Full File Name...........*/
              USHORT       idCommand), /* TMC_CREATE / TMC_OPEN...........*/

  ReadTmHeader (PTMT_GLOBALS ptmtg),  /* Tmt Globals area ................*/

  AllocTmtGlobals (USHORT usTmtGlobalsSize, /* The allocateion size.......*/
                   PPTMT_GLOBALS pptmtg),   /* The TM Globals Area........*/

  SetTmtWorkPointers (PTMT_GLOBALS ptmtg);  /* The TM Globals Area........*/

/*--------------------------------------------------------------------------*\
     Function prototypes.
\*--------------------------------------------------------------------------*/
VOID
GetFirstSegAddress
(
  PTMT_GLOBALS ptmtg,             // Pointer to Tmt globals
  PSZ          pszSource,         // pointer to source segment
  PTM_ADDRESS  pAddr              // pointer to address
);

VOID
CleanSource
(
   PTMT_GLOBALS ptmtg,            // Pointer to Tmt globals
   PSZ          pszSource         // Pointer to string to be tokenized
);

VOID
CalcPrimaryKey
(
  PTMT_GLOBALS ptmtg,             // Pointer to Globals structure
  PUCHAR       pchPrimaryKey      // Pointer to primary key
);

VOID
CalcSecondaryKey
(
  PTMT_GLOBALS ptmtg,             // Pointer to Tmt globals
  PSZ          pszSortedSecKey    // Ptr to sorted secondary key
);

VOID
Get4Chars
(
  PTMT_GLOBALS ptmtg,             // Pointer to Tmt globals
  SHORT        sTokenId,          // WORD/USELESS/NOISE/TEXT/TAG
  PTOKENENTRY  pteFirst,          // Ptr to Text or Word Table
  PUCHAR       pchPrimaryKey      // 4 chars for primary key
);

VOID
WordsTokenize
(
  PTMT_GLOBALS  ptmtg             // Pointer to Tmt globals
);

VOID
UselessFiltering
(
  PTOKENENTRY  pteWord            // Pointer to word in WordsTable
);

USHORT
Tmt
(
  HTM       htm,                  // Pointer to TmtGlobals
  PIN       pIn,                  // Pointer to input buffer
  POUT      pOut                  // Pointer to output buffer
);


/**********************************************************************/
/* TmtX                                                               */
/**********************************************************************/
USHORT
TmtX ( HTM       htm,                  // Pointer to TmtGlobals
       PXIN       pIn,                 // Pointer to input buffer
       PXOUT      pOut );              // Pointer to output buffer


USHORT
CalcEntryInKeyDir
(
  PTM_HEADER  ptmh,               // Pointer to Tm Header
  PUCHAR      pchPrimaryKey       // Primary Key
);

USHORT
WriteTmhToDisk
(
  PTMT_GLOBALS ptmtg,             // Pointer to globals
  USHORT       fsWrite            // Write control flags word
);

USHORT
WriteToDisk
(
  PTMT_GLOBALS ptmtg,             // TMT globals
  ULONG        ldispPtr,          // New file pointer location
  PVOID        pvWrite,           // Pointer to write buffer
  USHORT       numWrite           // Number of bytes to write
);

USHORT
FormatMore
(
  PTMT_GLOBALS ptmtg              // Pointer to Tmt globals
);

USHORT
ReadStringFromDisk
(
  PTMT_GLOBALS ptmtg,             // Pointer to Tmt globals
  PCHAR        bufRead,           // Read buffer
  USHORT       lenString,         // String length
  PTM_ADDRESS  paddr              // Pointer to string buffer
);

USHORT
ReadSegmentFromDisk
(
  PTMT_GLOBALS ptmtg,             // pointer to Tmt globals
  PTM_ADDRESS  pAddr,             // Pointer to an address
  PSEGMENT     pSegment,          // Pointer to seg. buffer
  PBOOL        pfFirstSeg,        // Pointer to 1st seg. flag
  PBOOL        pfLastSeg          // Pointer to last seg. flag
);

USHORT
ReadBlock
(
  PTMT_GLOBALS ptmtg,                // Pointer to Tmt globals
  PTM_ADDRESS  paddr,                // Pointer to an address
  BOOL         fAddressInParameter   // Address in pAddr
);

INT
CharCompare
(
  const void * arg1,                       // First comparand
  const void * arg2                        // Second comparand
);

BOOL
fStrcmpCRLF
(
  PSZ     pszStr1,           // pointer to first string to be compared
  PSZ     pszStr2,           // pointer to second string to be compared
  PUSHORT pusEqualChars,     // (return value) pointer to USHORT where the
                             // number of equal characters (first string)
  USHORT  fCompareType);     // flag indicating whether CRLF and LF are ignored
                             // ALIGN_CRLF -> CRLF and LF are equal   equal
                             // USE_CRLF   -> exact matches required s
                             // IGNORE_CRL -> characters are equal


/*--------------------------------------------------------------------------*\
     Function prototypes.
\*--------------------------------------------------------------------------*/
USHORT
  TmtExtract (PTMT_GLOBALS    ptmtg,           /* pointer to Tmt globals....*/
              PEXT_IN         pExtIn,          /* pointer to input buffer...*/
              PEXT_OUT        pExtOut);        /* pointer to output buffer..*/

USHORT
  TmtGet (PTMT_GLOBALS     ptmtg,              /* pointer to Tmt globals....*/
          PGET_IN          pGetIn,             /* pointer to input buffer...*/
          PGET_OUT         pGetOut),           /* pointer to output buffer..*/

  TmtGetTMPart( PTMT_GLOBALS  ptmtg,           /* pointer to Tmt globals....*/
                PGETPART_IN   pGetPartIn,      /* pointer to input buffer...*/
                PGETPART_OUT  pGetPartOut),    /* pointer to output buffer..*/

  GetSegByAddr (PTMT_GLOBALS     ptmtg,        /* pointer to TmtGlobals.....*/
                PTM_ADDRESS      pAddr,        /* pointer to input address..*/
                PTM_ADDRESS      pAddrNext,    /* pointer to next address...*/
                PSEGMENT         pseg),        /* pointer to segment........*/


  TmtInfo     (PTMT_GLOBALS     ptmtg,         /* pointer to Tmt globals....*/
               PINFO_OUT        pInfoOut);     /* pointer to output buffer..*/
/**********************************************************************/
/* TmtXInfo                                                          */
/**********************************************************************/
USHORT TmtXInfo( PTMX_CLB,
                 PTMX_INFO_OUT );


LONG
  CheckSimilar (PTMT_GLOBALS ptmtg,          /* pointer to Tmt globals.....*/
                PSEGMENT     pCurrentSegment,/* pointer to current segmnt .*/
                PTOKENENTRY  pTokenEntry,    /* points to 1'st & 2'nd word */
                PGET_IN      pGetIn,         /* pointer to input buffer....*/
                PSZ          pszInputKey,    /* pointer to sortedkey of....*/
                                             /* input segment..............*/
                PMATCH       pmtch),         /* pointer to stMatch.........*/

  CheckExact (PGET_IN      pGetIn,           /* pointer to input segment....*/
              PSEGMENT     pseg,             /* pointer to current seg......*/
              BOOL         fSimilarMod,      /* Similar= TRUE, Exact=FALSE..*/
              PMATCH       pmtch),           /* pointer to stMatch..........*/

  CalcExactIndustry (PGET_IN   pGetIn,       /* pointer to input segment....*/
                     PSEGMENT  pseg);        /* pointer to current seg......*/

VOID
  RankNewMatch (USHORT     numMatchesReq,    // number of matches required
                USHORT     usConvert,        // Conversion indicator
                PMATCH     pmtchCurrent,     // pointer to stMatch
                PSEGMENT   pseg,             // pointer to current seg
                PGET_OUT   pGetOut);         // pointer to GET_OUT struct

BOOL
  CheckWord   (PTOKENENTRY  pteFirst,       /*Point to first word ..........*/
               PTOKENENTRY  pteSecond) ;    /*Point to second word .........*/

VOID
LengthCorrectThresholds( PTMT_GLOBALS ptmtg,      //pointer to Tmt globals
                         USHORT       usLenInput, //number of words in inp. seg.
                         PGET_IN      pGetIn );            //pointer to input buffer

USHORT
  TmtAdd (PTMT_GLOBALS pTmtGlobals,        /* Pointer to Tmt Globals........*/
          PADD_IN      pAddIn,             /* Pointer to input buffer.......*/
          PADD_OUT     pAddOut),           /* Pointer to output buffer......*/

  TmtDelete (PTMT_GLOBALS ptmtg,               /* Pointer to Tmt Globals....*/
             PDEL_IN      pDeleteIn,           /* Pointer to input buffer...*/
             PDEL_OUT     pDeleteOut),         /* Pointer to output buffer..*/

  TmtReplace (PTMT_GLOBALS ptmtg,              /* Pointer to Tmt Globals....*/
              PREP_IN      pReplaceIn,         /* Pointer to input buffer...*/
              PREP_OUT     pReplaceOut),       /* Pointer to output buffer..*/

  AddSegToCluster (PTMT_GLOBALS  ptmtg,         /* Pointer to globals area..*/
                   PTM_ADDRESS   pAddr,         /* Ptr to initial address...*/
                   PSEGMENT      pseg),         /* Pointer to a segment.....*/

  FindFreshAddrInCluster (PTMT_GLOBALS ptmtg,     /* Pointer to Tmt globals.*/
                          PTM_ADDRESS  pAddr,     /* Pointer to address.....*/
                          BOOL fReadFirstBlock),  /* Read block flag........*/

  TakeBlockFromSpool (PTMT_GLOBALS ptmtg,     /* Pointer to Tmt globals.....*/
                      USHORT rcPrevious,      /* RC of the previous call....*/
                      PTM_ADDRESS  pAddr),    /* Pointer to an address......*/

  WriteStringToDisk (PTMT_GLOBALS ptmtg,      /* Pointer to Tmt globals.....*/
                     PCHAR   bufWrite,        /* Pointer to the string......*/
                     USHORT  lenString,       /* String length..............*/
                     PTM_ADDRESS  pAddr),     /* Pointer to string address..*/

  WriteBlock (PTMT_GLOBALS ptmtg),            /* Pointer to Tmt globals.....*/

  FindMatchSegInCluster (PTMT_GLOBALS ptmtg,        /* Ptr to Tmt globals...*/
                         PTM_ADDRESS  pAddr,        /* Pointer to address...*/
                         PBOOL        pfLastSeg,    /* Last segment flag....*/
                         PSEGMENT     psegIn,       /* Ptr to input buffer..*/
                         PSEGMENT     pseg),        /* Pointer to segment...*/

  DeleteSegment (PTMT_GLOBALS ptmtg,       /* Pointer to Tmt globals........*/
                PTM_ADDRESS   pAddr,       /* Address of segment to delete..*/
                BOOL          fLastSeg,    /* Last segment in cluster flag..*/
                PSEGMENT      pseg);       /* Pointer to the segment........*/

BOOL
  CheckMatchForDelete (PSEGMENT psegIn,    /* pointer to input buffer.......*/
                       PSEGMENT pseg);     /* currently, output buffer......*/

USHORT TmtDeleteTM( HTM        hMem,                 // TM handle
                    PDELTM_IN  pDelTmIn,             // Input structure
                    PDELTM_OUT pDelTmOut );          // Output structure
/**********************************************************************/
/* TmXtDeleteTM                                                       */
/**********************************************************************/
USHORT
TmtXDeleteTM( HTM,
              PTMX_DELTM_IN,
              PTMX_DELTM_OUT );

USHORT TmtCloseOrganize( HTM         hMem,           // TM handle
                         PENDORG_IN  pEndOrgIn,      // Input structure
                         PENDORG_OUT pEndOrgOut );   // Output structure
/**********************************************************************/
/* TmtXCloseOrganize                                                  */
/**********************************************************************/
USHORT
TmtXCloseOrganize( HTM,
                   PTMX_ENDORG_IN,
                   PTMX_ENDORG_OUT );


VOID   TmtDeleteFile( PDELFILE_IN  pDelFileIn,          // Input structure
                     PDELFILE_OUT pDelFileOut );       // Output structure

VOID   GetFileInfo( PFILEINFO_IN pFileInfoIn,        // Input structure
                    PFILEINFO_OUT pFileInfoOut );     // Output structure

VOID   RenameFile( PRENFILE_IN  pRenFileIn,          // Input structure
                   PRENFILE_OUT pRenFileOut );       // Output structure

BOOL fCheckFileClosed ( PSZ );         //--- pointer to file name


/*--------------------------------------------------------------------------*\
     Function prototypes.
\*--------------------------------------------------------------------------*/
USHORT
  TmtOpen (POPEN_IN   pOpenIn,           /* Pointer to input structure....*/
           POPEN_OUT  pOpenOut),         /* Pointer to output structure...*/

  TmtCreate (PCREATE_IN   pCreateIn,     /* Pointer to input structure....*/
             PCREATE_OUT  pCreateOut),   /* Pointer to output structure...*/

  TmtClose (PTMT_GLOBALS ptmtg,       /* Pointer to Globals structure.....*/
            PCLOSE_OUT   pCloseOut);  /* Pointer to output buffer.........*/

INT_PTR /*CALLBACK*/ MEMCREATEDLG( HWND, WINMSG, WPARAM, LPARAM );
INT_PTR /*CALLBACK*/ MEMLOADDLG( HWND, WINMSG, WPARAM, LPARAM );
INT_PTR /*CALLBACK*/ MEMEXPORTDLG( HWND, WINMSG, WPARAM, LPARAM );
INT_PTR /*CALLBACK*/ MEMMERGEDLG( HWND, WINMSG, WPARAM, LPARAM );
INT_PTR /*CALLBACK*/ MEMPROPDLG( HWND, WINMSG, WPARAM, LPARAM );
INT_PTR /*CALLBACK*/ MemCreateName( HWND, USHORT, WPARAM, LPARAM );
INT_PTR /*CALLBACK*/ UTLSERVERLISTDLG( HWND, WINMSG, WPARAM, LPARAM );
INT_PTR /*CALLBACK*/ UTLSERVERLISTNAMEDLG( HWND, WINMSG, WPARAM, LPARAM );
INT_PTR /*CALLBACK*/ MEMINCLUDEDLG( HWND, WINMSG, WPARAM, LPARAM );
INT_PTR /*CALLBACK*/ SERVWAITDLG( HWND, WINMSG, WPARAM, LPARAM );
USHORT  MemCreateProcess( PMEM_IDA, PSZ, USHORT );
VOID    MemDestroyProcess( PMEM_IDA, USHORT * );
USHORT  MemGetAddressOfProcessIDA( PMEM_IDA, WPARAM, USHORT *, PVOID * );
VOID    MemRcHandlingErrorUndefined( USHORT, PSZ );
VOID    MemRcHandlingErrorUndefinedHwnd( USHORT, PSZ, HWND );
USHORT  EQFMemOrganizeStart( PPROCESSCOMMAREA, HWND );
VOID    EQFMemOrganizeProcess( PPROCESSCOMMAREA, HWND );
VOID    EQFMemOrganizeEnd( PPROCESSCOMMAREA, HWND, LPARAM, BOOL );
VOID    EQFMemLoadStart( PPROCESSCOMMAREA, HWND );
VOID    EQFMemLoadProcess( PPROCESSCOMMAREA, HWND );
VOID    EQFMemLoadEnd( PPROCESSCOMMAREA, HWND, LPARAM );
USHORT  EQFMemExportStart( PPROCESSCOMMAREA, HWND );
USHORT  EQFMemExportProcess( PPROCESSCOMMAREA, HWND );
USHORT  EQFMemExportEnd( PPROCESSCOMMAREA, HWND, LPARAM );
VOID    EQFMemMergeStart( PPROCESSCOMMAREA, HWND );
VOID    EQFMemMergeProcess( PPROCESSCOMMAREA, HWND );
VOID    EQFMemMergeEnd( PPROCESSCOMMAREA, HWND, LPARAM );
USHORT  EQFMemImportTrojaStart( HWND, LPARAM, HWND );
USHORT  MemInitSlider( HWND, USHORT, PSZ, USHORT, PSZ, PHWND, USHORT, USHORT);
USHORT  ReadABGrouping( PSZ, PSZ, ABGROUP );
MRESULT MemOrganizeCallBack( PPROCESSCOMMAREA, HWND, WINMSG, WPARAM, LPARAM );
MRESULT MemExportCallBack( PPROCESSCOMMAREA, HWND, WINMSG, WPARAM, LPARAM );
MRESULT MemMergeCallBack( PPROCESSCOMMAREA, HWND, WINMSG, WPARAM, LPARAM );
MRESULT MemImportCallBack( PPROCESSCOMMAREA, HWND, WINMSG, WPARAM, LPARAM );



// ************* Memory macro definitions *******************************

//=======================================================================
//prototypes and definitions for TM utilities
#define SIZE_32K 32768
#define ERROR_TABLE_FULL 1111
#define ID_NOT_FOUND     2222


// adjust pointger for a new location
#define ADJUSTPTR( new, old, offsptr ) \
  ((PBYTE)new + ((PBYTE)offsptr - (PBYTE)old))

// do not update name tables when name is not contained in the table
#define NTMGETID_NOUPDATE_OPT 0x00000001

// returned ID if a name is not found in the table
#define NTMGETID_NOTFOUND_ID 0xFFFF

USHORT NTMGetIDFromNameEx
(
  PTMX_CLB    pTmClb,                  // input, memory control block pointer
  PSZ         pszName,                 // input, name being looked up
  PSZ         pszLongName,             // input, long name (only for FILE_KEY)
  USHORT      usTableType,             // input, type of table to use
  PUSHORT     pusID,                   // output, ID for name being looked up
  LONG        lOptions,                // input, additional options
  PUSHORT     pusAlternativeID         // output, alternative ID
);

PSZ NTMFindNameForID( PTMX_CLB pTmClb,      //input
                  PUSHORT  pusID,         //intput
                  USHORT   usTableType );



USHORT NTMGetIDFromName( PTMX_CLB, PSZ, PSZ, USHORT, PUSHORT );
USHORT NTMGetNameFromID( PTMX_CLB, PUSHORT, USHORT, PSZ, PSZ );
USHORT TmtXReplace( PTMX_CLB, PTMX_PUT_IN_W, PTMX_PUT_OUT_W );
USHORT TmtXGet( PTMX_CLB, PTMX_GET_IN_W, PTMX_GET_OUT_W );
USHORT TmtXCreate( PTMX_CREATE_IN, PTMX_CREATE_OUT );
USHORT TmtXOpen( PTMX_OPEN_IN, PTMX_OPEN_OUT );
USHORT TmtXClose( PTMX_CLB, PTMX_CLOSE_IN, PTMX_CLOSE_OUT );


//tm put prototypes
BOOL AllocTable( PTMX_TABLE* );
USHORT TokenizeSourceV5( PTMX_CLB, PTMX_SENTENCE_V5, PSZ, PSZ, USHORT );
USHORT TokenizeSourceEx2( PTMX_CLB, PTMX_SENTENCE, PSZ, PSZ, USHORT, ULONG, int );
VOID HashSentence( PTMX_SENTENCE, USHORT usMajVersion, USHORT usMinVersion );
VOID HashSentenceV5( PTMX_SENTENCE_V5, USHORT );
USHORT HashTupel( PBYTE, USHORT, USHORT );
USHORT HashTupelW( PSZ_W, USHORT, USHORT, USHORT );
static VOID BuildVotes( PTMX_SENTENCE );
static VOID Vote( PTMX_TERM_TOKEN, PTMX_SENTENCE, USHORT );
static VOID BuildVotesV5( PTMX_SENTENCE_V5 );
static VOID VoteV5( PTMX_TERM_TOKEN, PTMX_SENTENCE_V5, USHORT );
USHORT CheckCompactArea( PTMX_SENTENCE, PTMX_CLB );
USHORT CheckCompactAreaV5( PTMX_SENTENCE_V5, PTMX_CLB );

USHORT TokenizeTarget( PSZ_W, PSZ_W, PTMX_TAGTABLE_RECORD*, PLONG, PSZ, PUSHORT, PTMX_CLB );
USHORT TokenizeTargetV5( PSZ, PSZ, PTMX_TAGTABLE_RECORD*, PLONG, PSZ, PUSHORT, PTMX_CLB );

USHORT AddToTm( PTMX_SENTENCE, PTMX_CLB, PTMX_PUT_W, PULONG );
USHORT AddToTmV5( PTMX_SENTENCE_V5, PTMX_CLB, PTMX_PUT, PULONG );
VOID FillTmRecord( PTMX_SENTENCE, PTMX_TAGTABLE_RECORD, PSZ_W, USHORT,
                   PTMX_RECORD, PTMX_TARGET_CLB, USHORT );
VOID FillTmRecordV5( PTMX_SENTENCE_V5, PTMX_TAGTABLE_RECORD, PSZ, USHORT,
                   PTMX_RECORD, PTMX_OLD_TARGET_CLB );

USHORT FillClb( PTMX_TARGET_CLB *, PTMX_CLB, PTMX_PUT_W );
USHORT FillClbV5( PTMX_OLD_TARGET_CLB *, PTMX_CLB, PTMX_PUT );
USHORT UpdateTmIndex( PTMX_SENTENCE, ULONG, PTMX_CLB );
USHORT UpdateTmIndexV5( PTMX_SENTENCE_V5, ULONG, PTMX_CLB );
USHORT DetermineTmRecord( PTMX_CLB, PTMX_SENTENCE, PULONG );
USHORT DetermineTmRecordV5( PTMX_CLB, PTMX_SENTENCE_V5, PULONG );
USHORT UpdateTmRecord( PTMX_CLB, PTMX_PUT_W, PTMX_SENTENCE );
USHORT UpdateTmRecordV5( PTMX_CLB, PTMX_PUT, PTMX_SENTENCE_V5 );
USHORT AddTmTarget( PTMX_CLB, PTMX_PUT_W, PTMX_SENTENCE, PTMX_RECORD *, PULONG, PULONG );
USHORT AddTmTargetV5( PTMX_CLB, PTMX_PUT, PTMX_SENTENCE_V5, PTMX_RECORD *, PULONG, PULONG );
USHORT ComparePutData( PTMX_CLB, PTMX_RECORD *, PULONG, PTMX_PUT_W, PTMX_SENTENCE, PULONG );
USHORT ComparePutDataV5( PTMX_CLB, PTMX_RECORD *, PULONG, PTMX_PUT, PTMX_SENTENCE_V5, PULONG );

VOID FillTargetRecord( PTMX_SENTENCE, PTMX_TAGTABLE_RECORD,
                       PSZ_W, USHORT, PTMX_TARGET_RECORD *, PTMX_TARGET_CLB );
VOID FillTargetRecordV5( PTMX_SENTENCE_V5, PTMX_TAGTABLE_RECORD,
                       PSZ, USHORT, PTMX_TARGET_RECORD *, PTMX_OLD_TARGET_CLB );

USHORT ReplaceTmTarget( PTMX_SENTENCE, PTMX_CLB, PTMX_PUT, PBYTE,
                        PTMX_RECORD, PULONG );
VOID DeleteOldestRecord( PTMX_RECORD, PULONG );

//tm get prototypes
USHORT GetExactMatch( PTMX_CLB, PTMX_SENTENCE, PTMX_GET_W, PTMX_MATCH_TABLE_W,
                      PUSHORT, PTMX_GET_OUT_W );
USHORT ExactTest( PTMX_CLB, PTMX_RECORD, PTMX_GET_W, PTMX_SENTENCE,
                  PTMX_MATCH_TABLE_W, PUSHORT, ULONG );

BOOL AddTagsToString( PSZ, PULONG, PTMX_TAGTABLE_RECORD, PSZ );
BOOL AddTagsToStringW( PSZ_W, PLONG, PTMX_TAGTABLE_RECORD, PSZ_W );

INT CompCount( const void *, const void * );
INT CompCountVotes( const void *, const void * );
VOID CleanupTempMatch( PTMX_MATCHENTRY, PTMX_MATCHENTRY *, PUSHORT, PUSHORT );
USHORT FillMatchEntry( PTMX_CLB, PTMX_SENTENCE, PTMX_MATCHENTRY, PUSHORT );
USHORT FuzzyTest( PTMX_CLB, PTMX_RECORD, PTMX_GET_W, PTMX_MATCH_TABLE_W, PUSHORT,
                  PUSHORT, PUSHORT, PUSHORT, PTMX_SENTENCE, ULONG );
USHORT GetFuzzyMatch( PTMX_CLB, PTMX_SENTENCE, PTMX_GET_W, PTMX_MATCH_TABLE_W, PUSHORT );

//tm extract prototypes
USHORT TmtXExtract( PTMX_CLB, PTMX_EXT_IN_W, PTMX_EXT_OUT_W );
USHORT FillExtStructure( PTMX_CLB, PTMX_TARGET_RECORD,
                         PTMX_TARGET_CLB,
                         PSZ_W, PLONG, PTMX_EXT_W );

// TM segment update prototypes
USHORT TmtXUpdSeg
(
  PTMX_CLB    pTmClb,      // ptr to ctl block struct
  PTMX_PUT_IN pTmPutIn,    // ptr to put input data
  ULONG       ulUpdKey,    // SID of record being updated
  USHORT      usUpdTarget, // number of target being updated
  USHORT      usFlags      // flags controlling the updated fields
);

//tm delete segment prototypes
USHORT TmtXDelSegm( PTMX_CLB, PTMX_PUT_IN_W, PTMX_PUT_OUT_W );
USHORT FindTargetAndDelete( PTMX_CLB, PTMX_RECORD, PTMX_PUT_W, PTMX_SENTENCE, PULONG );
USHORT NTMCheckForUpdates( PTMX_CLB );
USHORT NTMLockTM( PTMX_CLB, BOOL, PBOOL );
USHORT MemBatchTMCreate( HWND hwnd, PDDEMEMCRT pMemCrt );
USHORT MemBatchTMExport( HWND hwnd, PDDEMEMEXP pMemExp );
USHORT MemBatchTMImport( HWND hwnd, PDDEMEMIMP pMemImp );
USHORT MemBatchTMDelete( HWND hwnd, PDDEMEMDEL pMemDel );

// definitions for terse of TM name tables
// max size of in-memory name table
#define SIZE_64K 0xFF00L

// magic word for recognition of tersed name tables
// Note: this ULONG value has to ensure that it will never been used
//       as a name so it is prefixed and suffixed by a 0x00
#define TERSEMAGICWORD 0x0019FF00L

// structure of header for tersed name tables
typedef struct _TERSEHEADER
{
  USHORT      usAllocSize;             // alloc size in untersed tables
  USHORT      usMaxEntries;            // max entries in untersed tables
  ULONG       ulMagicWord;             // magic word for tersed name
  USHORT      usDataSize;              // size of data area when expanded
  USHORT      usCompression;           // type of compression used for data
                                       // (values as defined in EQFCMPR.H)
} TERSEHEADER, *PTERSEHEADER;

USHORT NTMSaveNameTable
(
  PTMX_CLB    pTmClb,                  // ptr to TM control block
  ULONG       ulTableKey,              // key of table record
  PBYTE       pTMTable,                // ptr to table data
  ULONG       ulSize                   // size of table data
);

USHORT NTMLoadNameTable
(
  PTMX_CLB    pTmClb,                  // ptr to TM control block
  ULONG       ulTableKey,              // key of table record
  PBYTE       *ppTMTable,              // ptr to table data pointer
  PULONG      pulSize                  // ptr to buffer for size of table data
);


BOOL TMDelTargetClb
(
  PTMX_RECORD        pTmRecord,        // ptr to TM record
  PTMX_TARGET_RECORD pTargetRecord,    // ptr to target record within TM record
  PTMX_TARGET_CLB    pTargetClb        // ptr to target control record
);

BOOL TMDelTargetClbV5
(
  PTMX_RECORD         pTmRecord,        // ptr to TM record
  PTMX_TARGET_RECORD  pTargetRecord,    // ptr to target record within TM record
  PTMX_OLD_TARGET_CLB pTargetClb        // ptr to target control record
);

ULONG EQFUnicode2Compress( PBYTE pTarget, PSZ_W pInput, ULONG usLenChar );
ULONG EQFCompress2Unicode( PSZ_W pOutput, PBYTE pTarget, ULONG usLenComp );

// prototypes and functions for CPP versions of memory base code

#ifdef _OTMMEMORYPLUGIN_H_

/* !brief function handling the GUI mode of the memory import */
BOOL MemGUIExportMemory
( 
  OtmMemory *pMemory, 
  PLISTCOMMAREA pCommArea,
  PSZ pszMemName, 
  PSZ pszNameList,   
  PMEM_IDA      pIDA,                      // Pointer to the Main Memory data area
  HWND hwnd
);

/* !brief function handling the GUI mode of the memory merge */
BOOL MemGUIMergeMemory( OtmMemory *pMemory, PLISTCOMMAREA pCommArea, PSZ pszMemName, PMEM_IDA pIDA, HWND hwnd );

/* !brief function handling the GUI mode of the memory import */
BOOL MemGUIImportMemory( PLISTCOMMAREA pCommArea, PSZ pszMemName, PMEM_IDA pIDA, HWND hwnd );


#endif


typedef struct _MEM_ORGANIZE_IDA
{
 TMX_ENDORG_IN stEndOrgIn;                     // organize end input structure
 TMX_ENDORG_OUT stEndOrgOut;                   // organize end output structure
 TMX_PUT_IN_W  stPutIn;                        // input for TmReplace
 TMX_PUT_OUT_W stPutOut;                       // The REPLACE_OUT structure
 TMX_EXT_IN_W  stExtIn;                        // input for TmExtract
 TMX_EXT_OUT_W stExtOut;                       // output for TmExtract
 CHAR          szPathOrganizeMem[2048];        // Full path and name of TM to be organized
 CHAR          szDrive[MAX_DRIVE];             // Drive letter without colum
 CHAR          szMemName[MAX_LONGFILESPEC];    // Translation memory name 
 CHAR          szTempMemName[MAX_LONGFILESPEC];// name of temporary translation memory 
 CHAR          szPluginName[MAX_LONGFILESPEC]; // name of plugin used for the memory
 CHAR          szPathTempMem[2048];            // Full path of temporary transl. mem.
 OtmProposal   *pProposal;                     // buffer for memory proposal
 OtmMemory     *pMem;                           // Handle of transl. memory
 OtmMemory     *pMemTemp;                       // Handle of tmporary transl. memory
 BOOL          fMsg;                           // A message has been issued already
 ULONG         ulSegmentCounter;               // Number of segments organized
 ULONG         ulInvSegmentCounter;            // Invalid Segment counter
 TIME_L        tStamp;                         // Time stamp of organize start time
 HWND          hProgressWindow;                // Handle of progress indicator window
 ULONG         ulProgressPos;                  // position of progress indicator
 CHAR          szPathTempIndex[MAX_EQF_PATH];  //full temporary index name

 LANGUAGE      szSourceLanguage;               // source language of org TM
 LANGUAGE      szTargetLanguage;               // target language of org TM
 CHAR          szTagTable[MAX_FILESPEC];       // tag table of org TM

 CHAR          szPropertyName[MAX_FILESPEC];   // property name with ext.
 CHAR          szTempPropertyName[MAX_FILESPEC]; // property name temp TM with ext

 CHAR          szOrgProp[MAX_EQF_PATH];        // full name of original property file
 CHAR          szTmpProp[MAX_EQF_PATH];        // full name of temporary property file

 CHAR          szEqfPath[MAX_EQF_PATH];        // system path D:\EQF
 USHORT        usOrgType;                      // type ORGANIZE, CONVERT
 BOOL          fBatch;                 // TRUE if organizing in batch mode
 HWND          hwndErrMsg;             // handle of window to be used for error msgs
 PDDEMEMORG    pDDEMemOrg;             // ptr to batch memory organize data
 USHORT        usRC;                   // return code / error code
 LONG          NextTask;               // next task in non-DDE batch mode
 PSZ           pszNameList;            // pointer to list of TMs being organized
 PSZ           pszActiveName;          // points to current name in pszNameList
 CHAR          szBuffer[2048];         // general purpose buffer
 BOOL          fFirstGet;              // TRUE = this is the first get access
}MEM_ORGANIZE_IDA, * PMEM_ORGANIZE_IDA;

USHORT  TmCloseOrganize( PMEM_ORGANIZE_IDA, USHORT );

USHORT NTMCloseOrganize ( PMEM_ORGANIZE_IDA, USHORT            );

USHORT NTMConvertProperties( PPROPTRANSLMEM, PMEM_ORGANIZE_IDA );


/*! \brief constant defining the maximum number of opened memories
*/
#define OTMMEMSERVICE_MAX_NUMBER_OF_OPEN_MEMORIES 40
//5MB reserved for service
#define MEMORY_RESERVED_FOR_SERVICE 5000000


enum statusCodes {
  OK = 200, 
  INTERNAL_SERVER_ERROR = 500, 
  PROCESSING = 102, 
  NOT_FOUND = 404,
  BAD_REQUEST = 400,
  CONFLICT = 409,
  CREATED = 201,
  NOT_ACCEPTABLE = 406

};


struct ImportStatusDetails{
  std::atomic_short usProgress{0};
  std::atomic_int segmentsImported{-1};
  std::atomic_int invalidSegments{-1};
  std::atomic_int invalidSymbolErrors{-1};
  std::string importTimestamp;
  std::stringstream importMsg;
  
  void reset(){
    importMsg.str("");
    usProgress = 0;
    segmentsImported = -1;
    invalidSegments = -1;
    invalidSymbolErrors = -1;
    importTimestamp = "not finished";    
  }
  std::string toString(){
    std::string res;
    res = "progress = " + std::to_string(usProgress) + "; segmentsImported = " + std::to_string(segmentsImported) + "; invalidSegments = " + std::to_string(invalidSegments) + "; time = " + importTimestamp;
    return res;
  }
};


  /*! \brief States of a memory
  */
  typedef enum 
  {
    OPEN_STATUS,            // memory is available and open
    AVAILABLE_STATUS,       // memory has been imported but is not open yet
    IMPORT_RUNNING_STATUS,  // memory import is running
    IMPORT_FAILED_STATUS    // memory import failed
  } MEMORY_STATUS;

/*! \brief Info structure for an open translation memory
*/
typedef struct _OPENEDMEMORY
{
char szName[260];               // name of the memory
time_t tLastAccessTime;         // last time memory has been used
long lHandle;                   // memory handle     
MEMORY_STATUS eStatus;          // status of the memory
MEMORY_STATUS eImportStatus;    // status of the current/last memory import
//std::atomic<double> dImportProcess; 
//ushort * pusImportPersent = nullptr;
ImportStatusDetails* importDetails = nullptr;
char *pszError;                 // pointer to an error message (only when eStatus is IMPORT_FAILED_STATUS)
} OPENEDMEMORY, *POPENEDMEMORY;


#include "../source/opentm2/core/pluginmanager/OtmPlugin.h"

/*! \brief Abstract base-class for plugins handling translation memory
*/
class OtmMemoryPlugin: public OtmPlugin
{

public:

/*! \brief Constructor.
*/
	OtmMemoryPlugin()
		{pluginType = eTranslationMemoryType;};

/*! \brief Destructor.
*/
	virtual ~OtmMemoryPlugin()
		{};

	virtual bool isUsable()
		{return OtmPlugin::isUsable();};

	virtual const char* getName() = 0;

	virtual const char* getShortDescription() = 0;

	virtual const char* getLongDescription() = 0;

	virtual const char* getVersion() = 0;

	virtual const char* getSupplier() = 0;

	virtual const char* getDescriptiveMemType() = 0;
  
/*! \enum eRegRc
	Possible return values of OtmMemory and OtmMemoryPlugin methods
*/
	enum eRc
	{
		eSuccess = 0,			        /*!< method completed successfully */
		eUnknownPlugin,		        /*!< the specified memory plugin is not available */
//		eInvalidName,		          /*!< plugin-name is invalid */
//		eAlreadyRegistered,	      /*!< plugin with same name was already registered before */
//		eInvalidRequest,	        /*!< method may only be called from within registerPlugins call */
    eMemoryNotFound,          /*!< the specified memory does not exist or is not controlled by this memory plugin*/
		eUnknown,		            	/*!< plugin with that name was not registered before */
		eNotSupported,		        /*!< method is not supported by this plugin */
		eBufferTooSmall,          /*!< the provided buffer is too small */
    eNotSupportedMemoryType,
    eNotEnoughMemory,         /*!< not enough system memory to process the request */
    eRepeat                   /*!< repeat calling this method until processing has been completed*/
	};


 
/*! \brief Create a new translation memory
  \param pszName name of the new memory
	\param pszSourceLang source language
	\param pszDescription description of the memory
	\param bMsgHandling true/false: display errors or not
	\param hwnd owner-window needed for modal error-message
	\returns Pointer to created translation memory or NULL in case of errors
*/
	virtual OtmMemory* createMemory(
		const char* pszName,			  
		const char* pszSourceLang,
		const char* pszDescription,
		BOOL bMsgHandling,
		HWND hwnd
	) = 0;
	
/*! \brief Open an existing translation memory
  \param pszName name of the existing memory
	\param bMsgHandling true/false: display errors or not
	\param hwnd owner-window needed for modal error-message
  \param usAccessMode, special access mode for memory: FOR_ORGANIZE, EXCLUSIVE, READONLY
	\returns Pointer to translation memory or NULL in case of errors
*/
	virtual OtmMemory* openMemory(
		const char* pszName,			  
		BOOL bMsgHandling,
		HWND hwnd,
    unsigned short usAccessMode = 0
	) = 0;

/*! \brief Physically delete a translation memory
  \param pszName name of the memory being deleted
	\returns 0 if successful or error return code
*/
	virtual int deleteMemory(
		const char* pszName			  
	) = 0;

/*! \brief Clear (i.e. remove all entries) a translation memory
  \param pszName name of the memory being cleared
	\returns 0 if successful or error return code
*/
	virtual int clearMemory(
		const char* pszName			  
	) = 0;

  /*! \brief Closes a translation memory
  \param pMemory pointer to a previously opened memory object
	\returns 0 if successful or error return code
*/
	virtual int closeMemory(
		OtmMemory *pMemory			  
	) = 0;


  /*! \brief structure for memory information */
  typedef struct _MEMORYINFO
  {
    char szPlugin[256];                          // name of the plugin controlling this memory
    char szName[256];                            // name of the memory
    char szDescription[256];                     // description of the memory
    char szFullPath[256];                        // full path to memory file(s) (if applicable only)
    char szFullDataFilePath[256];                // full path to memory file(s) (if applicable only)
    char szFullIndexFilePath[256];               // full path to memory file(s) (if applicable only)
    char szSourceLanguage[MAX_LANG_LENGTH+1];    // memory source language
    char szOwner[256];                           // ID of the memory owner
    char szDescrMemoryType[256];                 // descriptive name of the memory type
    unsigned long ulSize;                        // size of the memory  
    BOOL fEnabled;                               // memory-is-enabled flag  
  } MEMORYINFO, *PMEMORYINFO;

/*! \brief type of callback function for ListMemories method */
typedef int (*PFN_LISTMEMORY_CALLBACK )(PVOID pvData, char *pszName, PMEMORYINFO pInfo  );

  /*! \brief Provide a list of all available memories
  \param pfnCallBack callback function to be called for each memory
	\param pvData caller's data pointetr, is passed to callback function
	\param fWithDetails TRUE = supply memory details, when this flag is set, 
  the pInfo parameter of the callback function is set otherwise it is NULL
	\returns number of provided memories
*/
	virtual int listMemories(
		PFN_LISTMEMORY_CALLBACK pfnCallBack,			  
		void *pvData,
		BOOL fWithDetails
	) = 0;

/*! \brief Get information about a memory
  \param pszName name of the memory
  \param pInfo pointer to buffer for memory information
	\returns 0 if successful or error return code
*/
	virtual int getMemoryInfo(
		const char* pszName,
    PMEMORYINFO pInfo
	) = 0;

/*! \brief provides a list of the memory data files

     This method returns a list of the files which together form the specific memory.
     If there are no real physical files also a dummy name can be and
     the contents of this dummy file can be generated dynamically when the getMemoryPart
     method is applied on this memory.

     The file names are passed to the getMemoryPart method to extract the memory data in
     binary form.

    \param pszName name of the memory
    \param pFileListBuffer  pointer to a buffer receiving the file names as a comma separated list
    \param iBufferSize      size of buffer in number of bytes

  	\returns 0 or error code in case of errors
*/
  virtual int getMemoryFiles
  (
    const char* pszName,
    char *pFileListBuffer,
    int  iBufferSize
  ) = 0;

// options for the importFromMemoryFiles method
static const int IMPORTFROMMEMFILES_COMPLETEINONECALL_OPT = 1;  // complete the import in one call, do not divide the processing into smaller steps

/*! \brief import a memory using a list of memory data files

    This method imports the binary files of a memory. The files have been created and
    filled using the getMemoryPart method.

    This method should delete the memory data files at the end of the processing- 

    When the processing of the memory files needs more time, the method
    should process the task in small units in order to prevent blocking of the
    calling application. To do this the method should return
    OtmMemoryPugin::eRepeat and should use the pPrivData pointer to anchor
    a private data area to keep track of the current processing step. The method will
    be called repetetively until the import has been completed.

   \param pszMemoryName    name of the memory 
   \param pFileList        pointer to a buffer containing the fully qualified memory data files as a comma separated list
   \param iOptions         processing options, one or more of the IMPORTFROMMEMFILES_..._OPT values ORed together
                           
   \param ppPrivateData    the address of a PVOID pointer which can be used to anchor private data. The
                           PVPOID pointer will be set to NULL on the initial call

  	\returns 0 if OK,
             OtmMemoryPlugin::eRepeat when the import needs more processing steps
             any other value is an error code
*/
virtual int importFromMemoryFiles
(
  const char *pszMemoryName,
  const char *pFileListBuffer,
  int  iOptions,
  PVOID *ppPrivateData
) = 0;

/*! \brief Physically rename a translation memory
  \param pszOldName name of the memory being rename
  \param pszNewName new name for the memory
	\returns 0 if successful or error return code
*/
  virtual int renameMemory(
	  const char* pszOldNae,
    const char* pszNewName
  ) = 0;

  /*! \brief Create a temporary memory
  \param pszPrefix prefix to be used for name of the temporary memory
  \param pszName buffer for the name of the temporary memory
	\param pszSourceLang source language
	\param bMsgHandling true/false: display errors or not
	\param hwnd owner-window needed for modal error-message
	\returns Pointer to created translation memory or NULL in case of errors
*/
  virtual OtmMemory* createTempMemory(
	  const char* pszPrefix,			  
	  const char* pszName,			  
	  const char* pszSourceLang,
	  BOOL bMsgHandling,
	  HWND hwnd
  ) = 0;

  /*! \brief Closes and deletes a temporary memory
  \param pMemory pointer to memory object
*/
  virtual void closeTempMemory(
	  OtmMemory *pMemory
  ) = 0;


/*! \brief Get the error message for the last error occured

    \param strError reference to a string receiving the error mesage text
  	\returns last error code
*/
	virtual int getLastError
  (
    std::string &strError
  ) = 0; 
/*! \brief Get the error message for the last error occured

    \param pszError pointer to a buffer for the error text
    \param iBufSize size of error text buffer in number of characters
  	\returns last error code
*/
	virtual int getLastError
  (
    char *pszError,
    int iBufSize
  ) = 0; 


/*! \brief Stops the plugin. 
	Terminating-function for the plugin, will be called directly before
	the DLL containing the plugin will be unloaded.\n
	The method should call PluginManager::deregisterPlugin() to tell the PluginManager
  that the plugin is not active anymore.
  Warning: THIS METHOD SHOULD BE CALLED BY THE PLUGINMANAGER ONLY!
	\param fForce, TRUE = force stop of the plugin even if functions are active, FALSE = only stop plugin when it is inactive
	\returns TRUE when successful */
	virtual bool stopPlugin( bool fForce = false ) = 0;

/*! \brief Returns list of supported drive letters. 
	The list of drives is used to allow the selection of a drive letter in the memory create indow
	The drive letters are retunred as a null-terminated string containing the letters of the 
  supported drives. When no drive selection should be possible, an empty string should be returned.\n
	\param pszDriveListBuffer points to the callers buffer for the list of drive letter characters
	\returns 0 if successful or error return code */
	virtual int getListOfSupportedDrives( char *pszDriveListBuffer ) = 0;

    /* \brief add a new memory information to memory list
       \param pszName memory name
       \returns 0 if success
   */
    virtual int addMemoryToList( const char* pszName ) = 0;

    /* \brief remove a memory information from memory list
       \param  pszName memory name
       \returns 0 if success
    */
    virtual int removeMemoryFromList( const char* pszName ) = 0;

 /* \brief Replace the data of one memory with the data of another memory and delete the remains of the second memory
    \param pszReplace name of the memory whose data is being replaced
    \param pszReplaceWith name of the memory whose data will be used to replace the data of the other memory
   \returns 0 if success
*/
 virtual int replaceMemory( const char* pszReplace, const char* pszReplaceWith ) = 0;


};



class TMManager{
    /*! \brief Pointer to the list of opened memories
    */
    std::vector<OPENEDMEMORY> vMemoryList;


public:

    /*! \brief OpenTM2 API session handle
    */
    LONG hSession = 0;
    /*! \brief close a memory and remove it from the open list
      \param iIndex index of memory in the open list
      \returns 0 
    */
    int removeFromMemoryList( int iIndex );

    /*! \brief close a memory and remove it from the open list
      \param pMem - pointer to mem
      \returns 0 
    */
    int removeFromMemoryList( POPENEDMEMORY pMem );

    /*! \brief get the handle for a memory, if the memory is not opened yet it will be openend
        \param pszMemory name of the memory
        \param plHandle buffer for the memory handle
        \param pszError buffer for an error message text in case of failures
        \param iErrorBufSize size of the error text buffer in number of characters
        \param piReturnCode pointer to a buffer for the OpenTM2 error code
        \returns OK if successful or an HTTP error code in case of failures
    */
    int getMemoryHandle( const std::string& memName , long *plHandle, wchar_t *pszError, int iErrorBufSize, int *piErrorCode );

    /*! \brief find a memory in our list of active memories
        \param pszMemory name of the memory
        \returns index in the memory table if successful, -1 if memory is not contained in the list
    */
    int findMemoryInList( const std::string& memName );

    /*! \brief find a free slot in our list of active memories, add a new entry if none found
        \returns index of the next free slot in the memory table or -1 if there is no free slot and the max number of entries has been reached
    */
    int getFreeSlot(size_t memoryRequested);
    POPENEDMEMORY getFreeSlotPointer(size_t memoryRequested);

    /*! \brief close any memories which haven't been used for a long time
        \returns 0
    */
    size_t cleanupMemoryList(size_t memoryRequested);

    /*! \brief calcuate total amount of RAM occupied by opened memory files
        \returns 0
    */
    size_t calculateOccupiedRAM();

    POPENEDMEMORY findOpenedMemory( const std::string& memName);

    int GetMemImportInProcess();
    void importDone(const std::string& memName, int iRC, char *pszError );
    
    /*! \brief Close all open memories
    \returns http return code0 if successful or an error code in case of failures
    */
    int closeAll();

///MEMORY FACTORY REGION
    /*! \brief   This class provides factory methods for OtmMemory objects 

*/

//public:


/*! \brief Error code definition
*/
  static const int ERROR_NOSHAREDMEMORYPLUGIN = 1001;
  static const int ERROR_PLUGINNOTAVAILABLE   = 1002;
  static const int ERROR_MEMORYOBJECTISNULL   = 1003;
  static const int ERROR_BUFFERTOOSMALL       = 1004;
  static const int ERROR_INVALIDOBJNAME       = 1005;
  static const int ERROR_MISSINGPARAMETER     = 1006;

/*! \brief Options for proposal sorting
*/
  static const LONG LATESTPROPOSAL_FIRST = 0x00000001;

  /*! \brief This static method returns a pointer to the TMManager object.
	The first call of the method creates the TMManager instance.
*/
  static TMManager* GetInstance();

  TMManager(){
    T5LOG( T5DEBUG) << "::Ctor of TMManager";
    pluginList = NULL;
    pHandleToMemoryList = new std::vector<OtmMemory *>;
    refreshPluginList();    
  }

/* \brief Open a memory 
   \param pszPlugin plugin-name or NULL if not available or memory object name is used
   \param pszMemoryName name of the memory being deleted or
    memory object name (pluginname + colon + memory name)
   \param piErrorCode pointer to a int varaibel receiving any error code when function fails
   \returns pointer to opened memory object 
*/
OtmMemory *openMemory
(
  char *pszPluginName,
  char *pszMemoryName,
  unsigned short usOpenFlags,
  int *piErrorCode
);

/* \brief Get information from an existing memory
   \param pszPlugin plugin-name or NULL if not available or memory object name is used
   \param pszMemoryName name of the memory or memory object name (pluginname + colon + memory name)
   \param pInfo pointer to caller MemoryInfo structure
   \returns 0 when successful or error code
*/
int getMemoryInfo
(
  char *pszPluginName,
  char *pszMemoryName,
  OtmMemoryPlugin::PMEMORYINFO pInfo
);


/* \brief Get the names of the actual memory data files

   These files are passed to the getMemoryPart method of the memory to retrieve the memory 
   data files in binary format (e.g. for folder export)

   \param pszPlugin plugin-name or NULL if not available or memory object name is used
   \param pszMemoryName name of the memory or memory object name (pluginname + colon + memory name)
   \param pFileListBuffer  pointer to a buffer receiving the file names as a comma separated list
   \param iBufferSize      size of buffer in number of bytes
   \param pszPluginNameOut buffer for the plugin of the memory or NULL, if not used
   \returns 0 when successful or error code
*/
int getMemoryFiles
(
  char *pszPluginName,
  char *pszMemoryName,
  char *pFileListBuffer,
  int  iBufferSize,
  char *pszPluginNameOut
);


/*! \brief import a memory using a list of memory data files

    This method imports the binary files of a memory. The files have been created and
    filled using the getMemoryPart method.

    This method should delete the memory data files at the end of the processing- 

    When the processing of the memory files needs more time, the method
    should process the task in small units in order to prevent blocking of the
    calling application. To do this the method should return
    OtmMemoryPugin::eRepeat and should use the pPrivData pointer to anchor
    a private data area to keep track of the current processing step. The method will
    be called repetetively until the import has been completed.

   \param pszPlugin plugin-name or NULL if not available or memory object name is used
   \param pszMemoryName name of the memory or memory object name (pluginname + colon + memory name)
   \param pFileList        pointer to a buffer containing the fully qualified memory data files as a comma separated list
   \param iOptions         processing options, one or more of the IMPORTFROMMEMFILES_..._OPT values ORed together
                           
   \param ppPrivateData    the address of a PVOID pointer which can be used to anchor private data. The
                           PVPOID pointer will be set to NULL on the initial call

  	\returns 0 if OK,
             OtmMemoryPlugin::eRepeat when the import needs more processing steps
             any other value is an error code
*/
int importFromMemoryFiles
(
  char *pszPluginName,
  char *pszMemoryName,
  char *pFileListBuffer,
  int  iOptions,
  PVOID *ppPrivateData
);


/* \brief Create a memory 
   \param pszPlugin plugin-name or NULL if not available or memory object name is used
   \param pszMemoryName name of the memory being created or
    memory object name (pluginname + colon + memory name)
   \param pszDescription description of the memory
   \param pszSourceLanguage source language of the memory
   \param pszOwner owner of the newly created memory
   \param bInvisible don't display memory in memory loist window when true, 
   \param piErrorCode pointer to a int varaibel receiving any error code when function fails
   \returns pointer to created memory object 
*/
OtmMemory *createMemory
(
  const char *pszPluginName,
  const char *pszMemoryName,
  const char *pszDescription,
  const char *pszSourceLanguage,
  const char *pszOwner,
  bool bInvisible,
  int *piErrorCode
);

/* \brief Create a memory 
   \param pszPlugin plugin-name or NULL if not available or memory object name is used
   \param pszMemoryName name of the memory being created or
    memory object name (pluginname + colon + memory name)
   \param pszDescription description of the memory
   \param pszSourceLanguage source language of the memory
   \param piErrorCode pointer to a int varaibel receiving any error code when function fails
   \returns pointer to created memory object 
*/
OtmMemory *createMemory
(
  const char *pszPluginName,
  const char *pszMemoryName,
  const char *pszDescription,
  const char *pszSourceLanguage,
  int *piErrorCode
);

OtmMemory* createMemory
(
  char *pszPluginName,
  char *pszMemoryName,
  char *pszDescription,
  char *pszSourceLanguage,
  char chDrive,
  char *pszOwner,
  bool bInvisible,
  int *piErrorCode
);

/* \brief List all available memories from all installed memory plugins
   \param pfnCallBack callback function to be called for each memory found
	 \param pvData caller's data pointetr, is passed to callback function
	 \param fWithDetails TRUE = supply memory details, when this flag is set, 
   the pInfo parameter of the callback function is set otherwise it is NULL
 	 \returns number of provided memories
*/
int listMemories
(
	OtmMemoryPlugin::PFN_LISTMEMORY_CALLBACK pfnCallBack,			  
	void *pvData,
	BOOL fWithDetails
);

/* \brief Get a list of the active memory plugins
   \param vPluginList reference to caller's vector receiving the list of memory plugins
   \param vPluginList reference to caller's vector receiving the list of shared memory plugins
 	 \returns number of provided plugins
*/
int getMemoryPlugins
(
	std::vector<OtmMemoryPlugin *>&vMemPluginList
);

/*! \brief Provide the names of shared memories available for a given user
	\param pszPlugin  name of the shared memory plugin to be used
	\param pvOptions pointer to a vector containing the access options
  \param pvConnected pointer to a vector receiving the names of the connected memories
  \param pvNotConnected pointer to a vector receiving the names of the not connected memories
	\returns number of provided memories
*/
	int listSharedMemories(
    char *pszPlugin,
    std::vector<std::string> *pvOptions,
    std::vector<std::string> *pvConnected,
    std::vector<std::string> *pvNotConnected
	);

/* \brief Close a memory 
   Close the memory object and free all memory related resources.
   The memory object is not valid anymore.
   \param pMemory pointer to the memory object being closes
   \returns 0 when successful or a error return code
*/
int closeMemory
(
  OtmMemory *pMemory
);

/*! \brief Rename a translation memory
  \param pszPluginName name of the memory being deleted
  \param pszOldMemoryName name of the memory being renamed or
  memory object name (pluginname + colon + memoryname)
  \param pszNewMemoryName new name for the memory 
	\returns 0 if successful or error return code
*/
int renameMemory(
  char *pszPluginName,
  char *pszOldMemoryName,
  char *pszNewMemoryName
);

/*! \brief Physically delete a translation memory
   \param pszPlugin plugin-name or NULL if not available or memory object name is used
  \param pszMemoryName name of the memory being deleted or
  memory object name (pluginname + colon + memoryname)
	\returns 0 if successful or error return code
*/
int deleteMemory(
  char *pszPluginName,
  char *pszMemoryName
);


/*! \brief Physically delete a translation memory
   \param pszPlugin plugin-name or NULL if not available or memory object name is used
  \param pszMemoryName name of the memory being deleted or
  memory object name (pluginname + colon + memoryname)
  \param strError  return error message with it
	\returns 0 if successful or error return code
*/
int deleteMemory(
  char *pszPluginName,
  char *pszMemoryName,
  std::string &strError
);
/*! \brief Delete all entries contained in a translation memory
  \param pszPlugin plugin-name or NULL if not available or memory object name is used
  \param pszMemoryName name of the memory being cleared or
  memory object name (pluginname + colon + memoryname)
	\returns 0 if successful or error return code
*/
int clearMemory(
  char *pszPluginName,
  char *pszMemoryName
);

/*! \brief Check if memory exists
  \param pszPlugin plugin-name or NULL if not available or memory object name is used
  \param pszMemoryName name of the memory being cleared or
  memory object name (pluginname + colon + memoryname)
	\returns 0 if successful or error return code
*/
int exists(
  const char *pszPluginName,
  const char *pszMemoryName
);

/*! \brief Check if memory is a shared/synchronized memory
  \param pMemory pointer to memory object
	\returns TRUE is memory is shared/synchronized
*/
BOOL isSharedMemory(
  OtmMemory *pMemory
);

/*! \brief Get name of default memory plugin
	\returns pointer to name of default memory plugin
*/
const char *getDefaultMemoryPlugin();

/*! \brief Show error message for the last error
  \param pszPlugin plugin-name or NULL if not available or memory object name is used
  \param pszMemoryName name of the memory causing the problem
  memory object name (pluginname + colon + memoryname)
  \param pMemory pointer to existing memory object or NULL if not available
  \param hwndErrMsg handle of parent window message box
*/
void showLastError(
  char *pszPluginName,
  char *pszMemoryName,
  OtmMemory *pMemory,
  HWND hwndErrMsg
);

/*! \brief   get error message for the last error
  \param   pMemory pointer to existing memory object or NULL if not available
  \param   iLastError the last error number
  \param   strError the error string returned with
  \returns the last error string
*/
std::string& getLastError(
    OtmMemory *pMemory,
    int& iLastError,
    std::string& strError);

/*! \brief Copy best matches from one proposal vector into another
  and sort the proposals
  \param SourceProposals refernce to a vector containing the source proposals
  \param TargetProposals reference to a vector receiving the copied proposals
  the vector may already contain proposals. The proposals are
  inserted on their relevance
  \param iMaxProposals maximum number of proposals to be filled in TargetProposals
  When there are more proposals available proposals with lesser relevance will be replaced
*/
void copyBestMatches(
  std::vector<OtmProposal *> &SourceProposals,
  std::vector<OtmProposal *> &TargetProposals,
  int iMaxProposals
);

/*! \brief Copy best matches from one proposal vector into another
  and sort the proposals
  \param SourceProposals refernce to a vector containing the source proposals
  \param TargetProposals reference to a vector receiving the copied proposals
  the vector may already contain proposals. The proposals are
  inserted on their relevance
  \param iMaxProposals maximum number of proposals to be filled in TargetProposals
  When there are more proposals available proposals with lesser relevance will be replaced
  \param iMTDisplayFactor factor for the placement of machine matches within the table
  \param fExactAndFuzzies switch to control the handling of fuzzy matches when exact matches exist, TRUE = keep fuzzy matches even when exact matches exist
  \param lOptions options for the sorting of the proposals
*/
void copyBestMatches(
  std::vector<OtmProposal *> &SourceProposals,
  std::vector<OtmProposal *> &TargetProposals,
  int iMaxProposals, 
  int iMTDisplayFactor,
  BOOL fExactAndFuzzies,
  LONG lOptions = 0
);

/*! \brief Insert proposal into proposal vector at the correct position and
  remove a proposal with lesser relevance when iMaxPropoals have already been filled
  \param NewProposal pointer to proposal being inserted
  \param SourceProposals refernce to a vector containing the source proposals
  \param TargetProposals reference to a vector receiving the copied proposals
  the vector may already contain proposals. The proposals are
  inserted on their relevance
  \param iMaxProposals maximum number of proposals to be filled in TargetProposals
  When there are more proposals available proposals with lesser relevance will be replaced
  \param fLastEntry true = this is the last entry in the table
  \param iMTDisplayFactor factor for the placement of machine matches within the table
  \param lOptions options for the sorting of the proposals
*/
void insertProposalData(
  OtmProposal *newProposal,
  std::vector<OtmProposal *> &Proposals,
  int iMaxProposals,
  BOOL fLastEntry, 
  int iMTDisplayFactor = -1,
  LONG lOptions = 0
);

/*! \brief Check if first proposal in the list can be used for automatic substitution 
  \param Proposals reference to a vector containing the proposals
  \returns true when automatic substitution can be performed otherwise false
*/
bool isAutoSubstCandidate(
  std::vector<OtmProposal *> &Proposals
);


/*! \brief Connect a shared memory
	\param pszPlugin  name of the shared memory plugin to be used
  \param hwndOwner owner handle for dialog windows
  \param pszMemoryName name of the memory
  \param pvOptions ptr to a vector containing the access options
  \returns 0 when successful or error return code
*/
int connectToMemory(
  char *pszPlugin,
  HWND hwndOwner,
  char *pszMemoryName,
  std::vector<std::string> *pvOptions
);

/*! \brief Disconnect a connected memory
	\param pszPlugin  name of the shared memory plugin to be used
  \param hwndOwner owner handle for dialog windows and error messages
  \param pszMemoryName name of the memory
  \returns 0 when successful or error return code
*/
int disconnectMemory(
  char *pszPlugin,
  HWND hwndOwner,
  char *pszMemoryName
);

/*! \brief get the options required to connect to a sharedmemory
	\param pszPlugin  name of the shared memory plugin to be used
  \param hwndOwner owner handle for dialog windows
  \param pvOptions pointer to a vector receiving the connect options
  \returns 0 when successful, -1 when user has cancelled the options dialog or an error code
*/
  int getConnectOptions(
    char *pszPlugin,
    HWND hwndOwner,
    std::vector<std::string> *pvOptions
  );

/*! \brief Get the object name for the memory
  \param pMemory pointer to the memory object
  \param pszObjName pointer to a buffer for the object name
  \param iBufSize size of the object name buffer
  \returns 0 when successful or the error code
*/
int getObjectName( OtmMemory *pMemory, char *pszObjName, int iBufSize );

/*! \brief Get the plugin name and the memory name from a memory object name
  \param pszObjName pointer to the memory object name
  \param pszPluginName pointer to the buffer for the plugin name or 
    NULL if no plugin name is requested
  \param iPluginBufSize size of the buffer for the plugin name
  \param pszluginName pointer to the buffer for the plugin name or
    NULL if no memory name is requested
  \param iNameBufSize size of the buffer for the memory name
  \returns 0 when successful or the error code
*/
int splitObjName( char *pszObjName, char *pszPluginName, int iPluginBufSize, char *pszMemoryName, int iNameBufSize  );

 /*! \brief Get the sort order key for a memory match
  \param Proposal reference to a proposal for which the sort key is evaluated
  \param iMTDisplayFactor the machine translation display factor, -1 to ignore the factor
  \param usContextRanking the context ranking for the proposal
  \param fEndIfTable TRUE when this proposal is the last in a proposal table
  When there are more proposals available proposals with lesser relevance will be replaced
  \returns the proposal sort key
*/
 int getProposalSortKey(  OtmProposal &Proposal, int iMTDisplayFactor, USHORT usContextRanking, BOOL fEndOfTable, LONG lOptions = 0 );

 /*! \brief Get the sort order key for a memory match
  \param Proposal reference to a proposal for which the sort key is evaluated
  \returns the proposal sort key
*/
int getProposalSortKey(  OtmProposal &Proposal );

 /*! \brief Get the sort order key for a memory match
  \param MatchType match type of the match
  \param ProposalType type of the proposal
  \param iFuzziness fuzziness of the proposal
  \param iMTDisplayFactor the machine translation display factor, -1 to use the system MT display factor
  \param usContextRanking the context ranking for the proposal
  \param fEndIfTable TRUE when this proposal is the last in a proposal table
  When there are more proposals available proposals with lesser relevance will be replaced
  \returns the proposal sort key
*/
int getProposalSortKey(  OtmProposal::eMatchType MatchType, OtmProposal::eProposalType ProposalType, int iFuzzyness, int iMTDisplayFactor, USHORT usContextRanking, BOOL fEndOfTable, LONG lOptions = 0 );

/* \brief add a new user to a shared memory user list
   \param pszPlugin  name of the shared memory plugin to be used
   \param pszMemName   memory name
   \param pszUserName  user name to add
   \param strError     return error message with it
   \returns 0
*/
int addSharedMemoryUser( char *pszPlugin, char *pszMemName, char *pszUserName, std::string &strError);

/* \brief delete a user from a shared memory user list
   \param pszPlugin  name of the shared memory plugin to be used
   \param pszMemName   memory name
   \param pszUserName  user name to add
   \param strError     return error message with it
   \returns 0
*/
int removeSharedMemoryUser( char *pszPlugin, char *pszMemName, char *pszUserName, std::string &strError);

/* \brief list shared memory users
   \param pszPlugin  name of the shared memory plugin to be used
   \param pszMemName   memory name
   \param users        users name returned
   \param strError     return error message with it
   \returns 0
*/
int listSharedMemoryUsers( char *pszPlugin, char  *pszMemName, std::vector<std::string> &users, std::string &strError);

/*! \brief Create a temporary memory
  \param pszPrefix prefix to be used for name of the temporary memory
  \param pszName buffer for the name of the temporary memory
	\param pszSourceLang source language
	\returns Pointer to created translation memory or NULL in case of errors
*/
 OtmMemory* createTempMemory(
	  const char* pszPrefix,			  
	  const char* pszName,			  
	  const char* pszSourceLang
  );

  /*! \brief Close and delete a temporary memory
  \param pMemory pointer to memory obhect
*/
 void closeTempMemory(
	  OtmMemory *pMemory
);

/* \brief add a new memory information to memory list
   \param pszName memory name, format as "pluginName:memoryName"
   \returns 0 if success
*/
int addMemoryToList(const char* pszName);

/* \brief remove a memory information from memory list
   \param  pszName format as "pluginName:memoryName"
   \returns 0 if success
*/
int removeMemoryFromList(const char* pszName);

  /*! \brief Replace a memory with the data from another memory
    This method bevaves like deleting the replace memory and renaming the
    replaceWith memory to the name of the replace memory without the overhead of the
    actual delete and rename operations
    \param pszPluginName name of plugin of the memory
    \param pszReplace name of the memory being replaced
    \param pszReplaceWith name of the memory replacing the pszReplace memory
	  returns 0 if successful or error return code
  */
  int replaceMemory
  (
    char *pszPluginName,
    char *pszReplace,
    char *pszReplaceWith
  );


  /*! \brief process the API call: EqfImportMemInInternalFormat and import a memory using the internal memory files
    \param pszMemory name of the memory being imported
    \param pszMemoryPackage name of a ZIP archive containing the memory files
    \param lOptions options for searching fuzzy segments
           - OVERWRITE_OPT overwrite any existing memory with the given name
    \returns 0 if successful or an error code in case of failures
  */
  USHORT APIImportMemInInternalFormat
  (
    const char*         pszMemoryName,
    const char*         pszMemoryPackage,
    LONG        lOptions 
  );

  /*! \brief process the API call: EqfExportMemInInternalFormat and export a memory to a ZIP package
    \param pszMemory name of the memory being exported
    \param pszMemoryPackage name of a new ZIP archive receiving the memory files
    \returns 0 if successful or an error code in case of failures
  */
  USHORT APIExportMemInInternalFormat
  (
    const char*         pszMemoryName,
    const char*         pszMemoryPackage,
    LONG        lOptions 
  );

  /*! \brief process the API call: EqfOpenMem and open the specified translation memory
    \param pszMemory name of the memory being opened
    \param plHandle buffer to a long value receiving the handle of the opened memory or -1 in case of failures
    \param lOptions processing options 
    \returns 0 if successful or an error code in case of failures
  */
  USHORT APIOpenMem
  (
    const char*         pszMemoryName, 
    LONG        *plHandle,
    LONG        lOptions 
  );

  /*! \brief process the API call: EqfCloseMem and close the translation memory referred by the handle
    \param lHandle handle of a previously opened memory
    \param lOptions processing options 
    \returns 0 if successful or an error code in case of failures
  */
  USHORT APICloseMem
  (
    LONG        lHandle,
    LONG        lOptions 
  );


  /*! \brief process the API call: EqfQueryMem and lookup a segment in the memory
    \param lHandle handle of a previously opened memory
    \param pSearchKey pointer to a MemProposal structure containing the searched criteria
    \param *piNumOfProsals pointer to the number of requested memory proposals, will be changed on return to the number of proposals found
    \param pProposals pointer to a array of MemProposal structures receiving the search results
    \param lOptions processing options 
    \returns 0 if successful or an error code in case of failures
  */
  USHORT APIQueryMem
  (
    LONG        lHandle,          
    PMEMPROPOSAL pSearchKey, 
    int         *piNumOfProsals,
    PMEMPROPOSAL pProposals, 
    LONG        lOptions     
  );


  /*! \brief process the API call: EqfSearchMem and search the given text string in the memory
    \param hSession the session handle returned by the EqfStartSession call
    \param lHandle handle of a previously opened memory
    \param pszSearchString pointer to the search string (in UTF-16 encoding)
    \param pszStartPosition pointer to a buffer (min size = 20 charachters) containing the start position, on completion this buffer is filled with the next search position
    \param pProposal pointer to an MemProposal structure receiving the next matching segment
    \param lSearchTime max time in milliseconds to search for a matching proposal, 0 for no search time restriction
    \param lOptions processing options
       SEARCH_IN_SOURCE_OPT  search in source
       SEARCH_IN_TARGET_OPT  search in target
    \returns 0 if successful or an error code in case of failures
  */
  USHORT APISearchMem
  (
    LONG        lHandle,                 
    wchar_t     *pszSearchString,
    const char* pszSrcLang, 
    const char* pszTrgLang,
    const char*         pszStartPosition,
    PMEMPROPOSAL pProposal,
    LONG        lSearchTime,
    LONG        lOptions
  );

  /*! \brief process the API call: EqfUpdateMem and update a segment in the memory
    \param lHandle handle of a previously opened memory
    \param pNewProposal pointer to an MemProposal structure containing the segment data
    \param lOptions processing options 
    \returns 0 if successful or an error code in case of failures
  */
  USHORT APIUpdateMem
  (
    LONG        lHandle, 
    PMEMPROPOSAL pNewProposal,
    LONG        lOptions
  );

    /*! \brief process the API call: EqfUpdateDeleteMem and deletes a segment in the memory
    \param lHandle handle of a previously opened memory
    \param pProposalToDelete pointer to an MemProposal structure containing the segment data
    \param lOptions processing options 
    \returns 0 if successful or an error code in case of failures
  */
  USHORT APIUpdateDeleteMem
  (
    LONG        lHandle, 
    PMEMPROPOSAL pProposalToDelete,
    LONG        lOptions,
    char*       errorStr
  );

  /*! \brief List the name of all memories
  \param hSession the session handle returned by the EqfStartSession call
  \param pszBuffer pointer to a buffer reiceiving the comma separated list of memory names or NULL to get the required length for the list
  \param plLength pointer to a variable containing the size of the buffer area, on return the length of name list is stored in this variable
  \returns 0 if successful or an error code in case of failures
  */
  USHORT APIListMem
  (
    const char*         pszBuffer,
    LONG        *plLength
  );

private:
  
  /* \brief Get memory plugin with the given plugin name
   \param pszPlugin plugin-name
   \returns pointer to plugin or NULL if no memory pluging with the given name is specified
*/
OtmPlugin *getPlugin
(
  const char *pszPluginName
);

  /* \brief Find memory plugin for this memory using input
    data or find memory testing all memory plugins
   \param pszPlugin plugin-name or NULL if not available
   \param pszMemoryName memory name or memory object name (pluginname + colon + memoryname)
   \returns pointer to plugin or NULL if no memory pluging with the given name is specified
*/
OtmPlugin *findPlugin
(
  const char *pszPluginName,
  const char *pszMemoryName
);

/* \brief Get the memory name from a potential memory object name
   \param pszMemoryName memory name or memory object name (pluginname + colon + memoryname)
   \param strMemoryName reference to string receiving memory name without any plugin name
   \returns 0
*/
int getMemoryName
(
  const char *pszMemoryName,
  std::string &strMemoryName
);


/* \brief Refresh internal list of memory plugins 
*/
void refreshPluginList();

/*! \brief get the index into the memory object table from a memory handle
  \param lHandle handle of a previously opened memory
  \returns index into the memory object table
*/
LONG getIndexFromHandle( LONG );

/*! \brief get the checksum from a memory handle
  \param lHandle handle of a previously opened memory
  \returns checksum of the memory object
*/
LONG getCheckSumFromHandle
(
  LONG        lHandle
);

/*! \brief compute the checksum for a memory object
  \param pMemory pointer to a memory object
  \returns memory object checksum
*/
LONG computeMemoryObjectChecksum( OtmMemory *pMemory );

/*! \brief convert a memory object and the index into the memory oject table to a memory handle
  \param lIndex index into the memory object table
  \param pMemory pointer to a memory object
  \returns index into the memory object table
*/
LONG createHandle
(
  LONG        lIndex,
  OtmMemory   *pMemory
);

/*! \brief compute the checksum for a memory object
  \param lHandle handel referring to the memory object
  \returns memory object pointer or NULL if the given handle is invalid
*/
OtmMemory *handleToMemoryObject
(
  LONG lHandle
);


/*! \brief search option flags
*/
#define SEARCH_SOURCE  1
#define SEARCH_TARGET  2
#define SEARCH_CASEINSENSITIVE 4
#define SEARCH_WHITESPACETOLERANT 8

/*! \brief search a string in a proposal
  \param pProposal pointer to the proposal 
  \param pszSearch pointer to the search string (when fIngoreCase is being used, this strign has to be in uppercase)
  \param lSearchOptions combination of search options
  \returns TRUE if the proposal contains the searched string otherwise FALSE is returned
*/
BOOL searchInProposal
( 
  OtmProposal *pProposal,
  PSZ_W pszSearch,
  LONG lSearchOptions
);

/*! \brief find the given string in the provided data
  \param pszData pointer to the data being searched
  \param pszSearch pointer to the search string
  \returns TRUE if the data contains the searched string otherwise FALSE is returned
*/
BOOL findString
( 
  PSZ_W pszData,
  PSZ_W pszSearch
);

/*! \brief check if search string matches current data
  \param pData pointer to current position in data area
  \param pSearch pointer to search string
  \returns 0 if search string matches data
*/
SHORT compareString
(
  PSZ_W   pData,
  PSZ_W   pSearch
);

/*! \brief normalize white space within a string by replacing single or multiple white space occurences to a single blank
  \param pszString pointer to the string being normalized
  \returns 0 in any case
*/
SHORT normalizeWhiteSpace
(
  PSZ_W   pszData
);

/*! \brief copy the data of a MEMPROPOSAL structure to a OtmProposal object
  \param pMemProposal pointer to MEMPROPOSAL structure 
  \param pOtmProposal pointer to OtmProposal object
  \returns 0 in any case
*/
void copyOtmProposalToMemProposal( OtmProposal *pOtmProposal, PMEMPROPOSAL pProposal  );

/*! \brief copy the data of a MEMPROPOSAL structure to a OtmProposal object
  \param pMemProposal pointer to MEMPROPOSAL structure 
  \param pOtmProposal pointer to OtmProposal object
  \returns 0 in any case
*/
void copyMemProposalToOtmProposal( PMEMPROPOSAL pProposal, OtmProposal *pOtmProposal );


/*! \brief Pointer to the list of installed memory plugins
*/
 std::vector<OtmMemoryPlugin *> *pluginList;

 /*! \brief error code of last error occured
*/
 int iLastError;

 /*! \brief error text for last error occured
*/
 std::string strLastError;

/*! \brief buffer for memory object names
*/
 char szMemObjName[512];

/*! \brief buffer for name of default memory plugin
*/
 char szDefaultMemoryPlugin[512];

/*! \brief buffer for name of default shared memory plugin
*/
 char szDefaultSharedMemoryPlugin[512];

/*! \brief array containing the memory objects referred to by a handle
*/
std::vector<OtmMemory *> *pHandleToMemoryList;

/*! \brief Buffer for segment text
*/
  CHAR_W m_szSegmentText[MAX_SEGMENT_SIZE+1];

  /*! \brief Buffer for search string
  */
  CHAR_W m_szSearchString[MAX_SEGMENT_SIZE + 1];


//end of MEMORY FACTORY region
};




////OTMFUNC region
/**
* \file tm.h
*
* \brief External header file for OpenTM2 API functions
*
*	Copyright Notice:
*
*	Copyright (C) 1990-2017, International Business Machines
*	Corporation and others. All rights reserved
**/

#ifndef _OTMFUNC_H_INCLUDED
#define _OTMFUNC_H_INCLUDED

#include "win_types.h"
#include "EQF.H"

#include "tm.h"

//#include "EQFFUNCI.H"
/*
#ifndef _EQF_H_INCLUDED
  typedef long LONG;
  typedef unsigned short USHORT;
  typedef unsigned short *PUSHORT;
  typedef char CHAR;
  typedef wchar_t CHAR_W;
  typedef char * PSZ;
  #define MAX_LANG_LENGTH           20   // length of the name of a language
  #define MAX_LONGFILESPEC         256   // max length of long file name + extension
  #define NUM_OF_FOLDER_DICS        10   // number of dictionaries per folder
  #define MAX_NUM_OF_READONLY_MDB   25   // folder's R/O memory dbs
  //#define MAX_FILESPEC              13   // max length of file name + extension
#endif
//*/

// include EQFPAPI.H for segment definitions
#ifndef _EQFPAPI_H_INCLUDED
  #include "EQFPAPI.H"
#endif 


typedef LONG HSESSION;
typedef HSESSION *PHSESSION;

typedef int BOOL;

typedef struct _REPORTTYPE
{
  PSZ  pszReport;
  LONG lRepType;
  PSZ  pszDescription;
} REPORTTYPE, *PREPORTTYPE;


typedef struct _REPORTSETTINGS
{
  PSZ  pszCountType;
  BOOL bShow;
  BOOL bSummary;
  PSZ  pszRepLayout;
  BOOL bShrink;
  PSZ  pszStatisticType;
  BOOL bExProposal;
} REPORTSETTINGS, *PREPORTSETTINGS;


typedef struct _FACTSHEET
{
  float lComplexity;
  float lPayFactor;
} FACTSHEET,*PFACTSHEET;


typedef struct _FINALFACTORS
{
  LONG  lUnit;
  float lCurrFactor;
  PSZ   pszLocalCurrency;
} FINALFACTORS,*PFINALFACTORS;


typedef struct _EXTFOLPROP
{
  CHAR  chDrive;
  CHAR  szTargetLang[MAX_LANG_LENGTH];
  CHAR  szRWMemory[MAX_LONGFILESPEC];
  CHAR  szROMemTbl[MAX_NUM_OF_READONLY_MDB][MAX_LONGFILESPEC];
  CHAR  szDicTbl[ NUM_OF_FOLDER_DICS][MAX_FILESPEC];
} EXTFOLPROP, *PEXTFOLPROP;
//
// option flags used by the function call interface
//

#define NO_ERROR 0

// location flags for TMs and dictionaries
#define LOCAL_OPT         0x00000001L
#define SHARED_OPT        0x00000002L

// analysis flags 
#define TMMATCH_OPT            0x00000010L
#define ADDTOMEM_OPT           0x00000020L
#define AUTOSUBST_OPT          0x00000040L
#define UNTRANSLATED_OPT       0x00000080L
#define AUTOLAST_OPT           0x00000100L
#define AUTOJOIN_OPT           0x00000200L
#define AUTOCONTEXT_OPT        0x00000400L
#define REDUNDCOUNT_OPT        0x00000800L
#define IGNOREPATH_OPT         0x00001000L
#define ADJUSTLEADWS_OPT       0x00002000L
#define ADJUSTTRAILWS_OPT      0x00004000L
#define RESPECTCRLF_OPT        0x00008000L
#define NOBLANKATSEGEND_OPT    0x00010000L
#define NOSUBSTIFIDENTICAL_OPT 0x00020000L
#define SENDTOMT_OPT           0x00080000L
#define STOPATFIRSTEXACT_OPT   0x00100000L
// ignore memory proposals which are flagged with a comment

#define IGNORECOMMENTED_OPT    0x00200000L

/** @brief protect text inside XMP sections, MsgNum sections, Meta sections, screen sections, and code block sections */
#define PROTECTXMPSCREEN_OPT   0x00040000L

/** @brief protect text inside XMP sections */
#define PROTECTXMP_OPT         0x00400000L
/** @brief protect text inside MsgNum sections */
#define PROTECTMSGNUM_OPT      0x00800000L
/** @brief protect text inside Meta sections */
#define PROTECTMETA_OPT        0x01000000L
/** @brief protect text inside screen sections */
#define PROTECTSCREEN_OPT      0x02000000L
/** @brief protect text inside CodeBlock sections */
#define PROTECTCODEBLOCK_OPT   0x04000000L


// folder export and folder import flags
#define WITHDICT_OPT           0x00001000L
#define WITHMEM_OPT            0x00002000L
#define DELETE_OPT             0x00004000L
#define WITHREADONLYMEM_OPT    0x00008000L
#define WITHDOCMEM_OPT         0x00010000L
#define MASTERFOLDER_OPT       0x00020000L
#define XLIFF_OPT              0x00040000L
#define NOMARKUP_UPDATE_OPT    0x00080000L
#define WO_REDUNDANCY_DATA_OPT 0x00100000L

//
// document import specific options
//

// do not search in sub-directories for specified document names
#define NOSUBDIRSEARCH_OPT  0x00001000L

//
// flags for document export and wordcount
//

// Count replace matches separately option (can only be used in conjunction with TMMATCH_OPT)
#define SEPERATEREPLMATCH_OPT  0x02000000L

// create word count without duplicates (R009560)
#define DUPMEMMATCH_OPT   0x01000000L

// create word count without duplicates (R009560)
#define DUPLICATE_OPT     0x00010000L

// create source word count / export source document
#define SOURCE_OPT        0x00020000L

// create translated/untranslated word count / export target document
#define TARGET_OPT        0x00040000L

// export SNOMATCH document
#define SNOMATCH_OPT      0x00080000L

// count fuzzy matches (only EqfCountWords)
#define FUZZYMATCH_OPT         0x00080000L

//

// flags for dictionary import merge options
// (IGNORE_OPT also used in EqfImportMem to skip invalid segments)
//
#define IGNORE_OPT        0x00000020L
#define REPLACE_OPT       0x00000040L
#define COMBINE_OPT       0x00000080L

// flags for dictionary import/export in DXT UTF8 format
#define DXT_UTF8_OPT     0x00200000L

// external/internal flags
#define EXTERNAL_OPT      0x01000000L
#define INTERNAL_OPT      0x02000000L

// flags for build archive TM function EqfArchiveTM
#define USEASFOLDERTM_OPT   0x20000000L
#define SOURCESOURCEMEM_OPT 0x40000000L
#define SETMFLAG_OPT        0x80000000L

// general flags
#define OVERWRITE_OPT     0x10000000L

// characterset flags for dictionary/memory import and export
#define ASCII_OPT        0x00020000L
#define ANSI_OPT         0x00040000L
#define UTF16_OPT        0x00080000L

// import in TMX format (UTF-16 and UTF-8)
#define TMX_OPT          0x00100000L

// export in TMX format
#define TMX_UTF16_OPT    0x00100000L
#define TMX_UTF8_OPT     0x00200000L

// clean/remove RTF tags
#define CLEANRTF_OPT     0x00400000L

// restrict RTF tag removal to tags enclosed in curly braces only
#define INCURLYBRACE_OPT   0x00800000L

// remove linebreaks in text of translation units
#define TMX_NOCRLF_OPT     0x01000000L

// import in XLIFF machine translation (MT) format
#define XLIFF_MT_OPT       0x02000000L

// how to handle unknown markup table when importing memory
#define CANCEL_UNKNOWN_MARKUP_OPT      0x10000000L
#define SKIP_UNKNOWN_MARKUP_OPT        0x20000000L
#define GENERIC_UNKNOWN_MARKUP_OPT     0x40000000L

// option for EqfImportMemEx only: create a new segment match ID even if the match has one already
#define FORCENEWMATCHID_OPT 0x00000004L

// flags for document export in validation format

// export documents in validation format (cannot be used together with the other export options)
// export validation document in XML format
#define VALFORMAT_XML_OPT    0x00200000L  
// export validation document in HML format
#define VALFORMAT_HTML_OPT   0x00400000L  
//export validation document in DOC format
#define VALFORMAT_DOC_OPT    0x00800000L  
//export validation document in ODT format
#define VALFORMAT_ODT_OPT    0x00100000L  
//export validation document in DOCX format
#define VALFORMAT_DOCX_OPT    0x08000000L  

// flags which can be used together with the export options above

// combine documents into a single file 
#define VALFORMAT_COMBINE_OPT  0x01000000L  
// include protected segments in the validation document
#define VALFORMAT_PROTSEGS_OPT 0x02000000L  

// export documents as plain XML
#define PLAINXML_OPT           0x04000000L

// relative path document export options
#define WITHRELATIVEPATH_OPT      0x20000000L
#define WITHOUTRELATIVEPATH_OPT   0x40000000L

// document export/import in internal format
#define OPENTM2FORMAT_OPT 0x80000000L

// include TVT tracking ID document export option
#define WITHTRACKID_OPT 0x08000000L

//
// output type options for EqfCountWords and EqfCreateCountReport
//
#define TEXT_OUTPUT_OPT   0x00100000L  
#define XML_OUTPUT_OPT    0x00200000L  
#define HTML_OUTPUT_OPT   0x00400000L  

// report IDs for function EqfCreateCountReport
#define HISTORY_REP             1
#define COUNTING_REP            2
#define CALCULATING_REP         3
#define PREANALYSIS_REP         4
#define REDUNDANCY_REP          5
#define REDUNDANCYSEGMENT_REP   6

// report types for function EqfCreateCountReport

// types for HISTORY_REPORT
#define BRIEF_SORTBYDATE_REPTYPE  1
#define BRIEF_SORTBYDOC_REPTYPE   2
#define DETAIL_REPTYPE            3

// types for COUNTING_REPORT
#define WITHTOTALS_REPTYPE        4
#define WITHOUTTOTALS_REPTYPE     5

// types for CALCULATING_REPORT, PREANALYSIS_REPORT, REDUNDANCY_REPORT,
//           and REDUNDANCYSEGMENT_REPORT
#define BASE_REPTYPE                    6
#define BASE_SUMMARY_REPTYPE            7
#define BASE_SUMMARY_FACTSHEET_REPTYPE  8
#define SUMMARY_FACTSHEET_REPTYPE       9
#define FACTSHEET_REPTYPE              10


//options for EqfCreateITM lType
#define NOANA_TYP           0x1
#define NOTM_TYP            0x2
#define PREPARE_TYP         0x4

//options for EqfChangeMFlag lAction
#define CLEAR_MMOPT         0
#define SET_MMOPT           1

// options for non-dde interface (calculating report)
#define BASE_TYP              1
#define FACT_TYP              2
#define SUM_TYP               4
#define BRIEF_SORTBYDATE_TYP  8
#define BRIEF_SORTBYDOC_TYP  16
#define DETAIL_TYP           32


#define PLAUS_OPT   1             // (Plausibilty check)
#define LOST_OPT    2             // (Lost Data: Force new shipment)
#define LIST_OPT    4             // (List of Documents)

// option for fuzzy segment search to mark the differences in the output file
#define MARKDIFFERENCES_OPT 0x08000000L

// fuzzy segment search modes
#define UPTOSELECTEDCLASS_MODE 0
#define SELECTEDCLASSANDHIGHER_MODE 1
#define ONLYSELECTEDCLASS_MODE 2

// concordance search modes
#define SEARCH_IN_SOURCE_OPT  0x00020000L
#define SEARCH_IN_TARGET_OPT  0x00040000L
#define SEARCH_CASEINSENSITIVE_OPT 0x00080000L
#define SEARCH_WHITESPACETOLERANT_OPT 0x00100000L


#define SEARCH_EXACT_MATCH_OF_SRC_LANG_OPT 0x00200000L
#define SEARCH_GROUP_MATCH_OF_SRC_LANG_OPT 0x00400000L
#define SEARCH_EXACT_MATCH_OF_TRG_LANG_OPT 0x00800000L
#define SEARCH_GROUP_MATCH_OF_TRG_LANG_OPT 0x01000000L

// return when all activitiy has been completed (instead of iterative processing)
#define COMPLETE_IN_ONE_CALL_OPT 0x01000000

// non-DDE function interface specific return codes

// Info: return code for functions not implemented yet
#define NOTIMPLEMENTED_RC               10001

// Error: passed session handle is invalid
#define ERROR_INVALID_SESSION_HANDLE    10002

// Notification: current function has not been completed yet
//               re-call function until a non-CONTINUE_RC
//               return code is retuned
#define CONTINUE_RC                     10003

// Error: Wrong or conflicting options specified
#define WRONG_OPTIONS_RC                10004

// Error: different function has been called although
//        current task has not been completed yet
#define LASTTASK_INCOMPLETE_RC          10005

// Error: Segment has been joined to a previous one and is not
//        part of the visible document. It cannot be used
//        in function EqfGetSourceLine
#define SEGMENTISJOINED_RC               10006

// Error: Given segment number is invalid
//        (probably not contained in document)
#define INVALIDSEGMENT_RC                10007

// Error: Given handle of loaded file is invalid
#define INVALIDFILEHANDLE_RC             10008

// Error: There is no segment matching the given position
#define NOMATCHINGSEGMENT_RC             10009

// Info: End if data reached
#define ENDREACHED_RC                    10010

// Info: Time out occurend (eceeded given search time)
#define TIMEOUT_RC                    10011

/*! \brief Create a new folder
    \param hSession the session handle returned by the EqfStartSession call
    \param pszFolderName pointer to the buffer containing the folder name
	\param pszDescription pointer to the buffer containing the folder description or NULL if not used
	\param chTargetDrive the drive letter of the drive the folder should reside on, if left empty the folder is created on the OpenTM2 installation drive
	\param pszMemname pointer to the buffer containing the folder Translation Memory
	\param pszMarkup pointer to the buffer containing the name of the folder markup (e.g. IBMDITA)
	\param pszEditor pointer to the buffer containing the name of the editor to be used for documents of this folder
	\param pszDictionaries pointer to the buffer containing a comma separated list of dictionaries or NULL if no dictionaries should be used
	\param pszSourceLanguage pointer to the buffer containing the folder source language (OpenTM2 language name)
	\param pszTargetLanguage pointer to the buffer containing the folder target language (OpenTM2 language name)
	\param pszConversion pointer to the buffer containing the export conversion - currently not in use and should be NULL 
	\param pszReadOnlyMems pointer to the buffer containing the a comma separated list of readonly Translation Memory databases or NULL if not used
	\returns 0 if successful or an error code in case of failures
*/
/*@ADDTOSCRIPTER*/  
USHORT EqfCreateFolder
(
  HSESSION    hSession,                // mand: Eqf session handle
  PSZ         pszFolderName,           // mand: name of folder
  PSZ         pszDescription,          // opt: folder description or NULL
  CHAR        chTargetDrive,           // opt: folder target drive
  PSZ         pszMemname,              // mand: folder Translation Memory
  PSZ         pszMarkup,               // mand: folder markup
  PSZ         pszEditor,               // opt: folder editor
  PSZ         pszDictionaries,         // opt: list of dictionaries or NULL
  PSZ         pszSourceLanguage,       // mand: folder source language
  PSZ         pszTargetLanguage,       // mand: folder target language
  PSZ         pszConversion,           // opt: export conversion or NULL
  PSZ         pszReadOnlyMems          // opt: list of readonly TMs or NULL
);


// create a new controlled folder
/*! \brief Create a new cntrolled/protected folder
    A controlled folder has some protected properties 
	\param hSession the session handle returned by the EqfStartSession call
	\param pszFolderName pointer to the buffer containing the folder name
	\param pszDescription pointer to the buffer containing the folder description or NULL if not used
	\param chTargetDrive the drive letter of the drive the folder should reside on, if left empty the folder is created on the OpenTM2 installation drive
	\param pszMemname pointer to the buffer containing the folder Translation Memory
	\param pszMarkup pointer to the buffer containing the name of the folder markup (e.g. IBMDITA)
	\param pszEditor pointer to the buffer containing the name of the editor to be used for documents of this folder
	\param pszDictionaries pointer to the buffer containing a comma separated list of dictionaries or NULL if no dictionaries should be used
	\param pszSourceLanguage pointer to the buffer containing the folder source language (OpenTM2 language name)
	\param pszTargetLanguage pointer to the buffer containing the folder target language (OpenTM2 language name)
	\param pszConversion pointer to the buffer containing the export conversion - currently not in use and should be NULL
	\param pszReadOnlyMems pointer to the buffer containing the a comma separated list of read only Translation Memory databases or NULL if not used
	\param pszPassword pointer to the buffer containing the password to be used for the folder
	\param pszProjCoordName pointer to the buffer containing the name of the project coordinator or NULL if not used
	\param pszProjCoordMail pointer to the buffer containing the project coordinator's mail or NULL if not used
	\param pszTranslatorName pointer to the buffer containing the name of the translator
	\param pszTranslatorMail pointer to the buffer containing the translator's mail
	\param pszProductName pointer to the buffer containing the name of the product
	\param pszProductFamily pointer to the buffer containing the product family
	\param pszSimilarProduct pointer to the buffer containing the similar product family
	\param pszProductDict pointer to the buffer containing the product subject area dictionary
	\param pszProductMem pointer to the buffer containing the product subject area memory
	\param pszPreviousVersion pointer to the buffer containing the previous version of the product
	\param pszVersion pointer to the buffer containing the Version of the product
	\param pszShipmentNumber pointer to the buffer containing the shipment number
	\returns 0 if successful or an error code in case of failures
*/
/*@ADDTOSCRIPTER*/  
USHORT EqfCreateControlledFolder
(
  HSESSION    hSession,                // mand: Eqf session handle
  PSZ         pszFolderName,           // mand: name of folder
  PSZ         pszDescription,          // opt: folder description or NULL
  CHAR        chTargetDrive,           // opt: folder target drive
  PSZ         pszMemname,              // mand: folder Translation Memory
  PSZ         pszMarkup,               // mand: folder markup
  PSZ         pszEditor,               // opt: folder editor
  PSZ         pszDictionaries,         // opt: list of dictionaries or NULL
  PSZ         pszSourceLanguage,       // mand: folder source language
  PSZ         pszTargetLanguage,       // mand: folder target language
  PSZ         pszConversion,           // opt: export conversion or NULL
  PSZ         pszReadOnlyMems,         // opt: list of readonly TMs or NULL
  PSZ         pszPassword,             // mand: password
  PSZ         pszProjCoordName,        // opt: name of the project coordinator
  PSZ         pszProjCoordMail,        // opt: project coordinator's mail
  PSZ         pszTranslatorName,       // opt: name of the translator
  PSZ         pszTranslatorMail,       // opt: translator's mail
  PSZ         pszProductName,          // opt: Name of the product
  PSZ         pszProductFamily,        // opt: Product Famiily
  PSZ         pszSimilarProduct,       // opt: Similar Product Family
  PSZ         pszProductDict,          // opt: Product subject area dictionary
  PSZ         pszProductMem,           // opt: Product subject area memory
  PSZ         pszPreviousVersion,      // opt: Previous version of the product
  PSZ         pszVersion,              // opt: Version of the Product
  PSZ         pszShipmentNumber        // opt: Shipment number
 );
// change Folder Properties
/*! \brief Change the properties of a folder
	\param hSession the session handle returned by the EqfStartSession call
	\param pszFolderName pointer to the buffer containing the folder name
	\param chTargetDrive the drive letter of the drive the folder resides on (is not required anymore and should be left empty
	\param pszTargetLanguage pointer to the buffer containing the new folder target language (OpenTM2 language name) or NULL when the target language should not be changed
	\param pszMemName pointer to the buffer containing the name of the new folder Translation Memory or NULL when the target language should not be changed
	\param pszDictionaries pointer to the buffer containing the comma separated new list of dictionaries or NULL if dictionaries should not be changed
	\returns 0 if successful or an error code in case of failures
*/
/*@ADDTOSCRIPTER*/ 
USHORT EqfChangeFolProps
(
  HSESSION    hSession,                // mand: Eqf session handle
  PSZ         pszFolderName,           // mand: name of folder
  CHAR        chTargetDrive,           // opt: target drive
  PSZ         pszTargetLanguage,       // opt: target language or NULL
  PSZ         pszMemName,              // opt: folder Translation Memory or NULL
  PSZ         pszDictionaries          // opt: list of dictionaries or NULL
  );
/*! \brief Change the properties of a folder (extended version)
  \param hSession the session handle returned by the EqfStartSession call
  \param pszFolderName pointer to the buffer containing the folder name
  \param chTargetDrive the drive letter of the drive the folder resides on (is not required anymore and should be left empty
  \param pszTargetLanguage pointer to the buffer containing the new folder target language (OpenTM2 language name) or NULL for no change
  \param pszMemName pointer to the buffer containing the name of the new folder Translation Memory or NULL for no change
  \param pszDictionaries pointer to the buffer containing the comma separated new list of dictionaries or NULL for no change
  \param pszROMemories pointer to the buffer containing the new list of read-only Translation Memory databases or NULL for no change
  \param pszDescription pointer to the buffer containing the new folder description or NULL for no change
  \param pszProfile pointer to the buffer containing the new calculation profile name or NULL for no change
  \param pszShipment pointer to the buffer containing the new folder shipment number or NULL for no change
  \returns 0 if successful or an error code in case of failures
  */
/*@ADDTOSCRIPTER*/ 
USHORT EqfChangeFolPropsEx
(
  HSESSION    hSession,                // mand: Eqf session handle
  PSZ         pszFolderName,           // mand: name of folder
  CHAR        chTargetDrive,           // opt: target drive
  PSZ         pszTargetLanguage,       // opt: target language or NULL
  PSZ         pszMemName,              // opt: folder Translation Memory or NULL
  PSZ         pszDictionaries,         // opt: list of dictionaries or NULL
  PSZ         pszROMemories,           // opt: list of read-only search memories or NULL
  PSZ         pszDescription,          // opt: folder description or NULL
  PSZ         pszProfile,              // opt: calculation profile name or NULL
  PSZ         pszShipment              // opt: new folder shipment number or NULL
  );
/*! \brief Create a sub-folder
	\param hSession the session handle returned by the EqfStartSession call
	\param pszParentFolder pointer to the buffer containing the name of the parent folder
	\param pszSubFolderName pointer to the buffer containing the name for the new sub-folder
	\param pszMemname pointer to the buffer containing the folder Translation Memory
	\param pszMarkup pointer to the buffer containing the name of the folder markup (e.g. IBMDITA)
	\param pszSourceLanguage pointer to the buffer containing the sub-folder source language (OpenTM2 language name)
	\param pszTargetLanguage pointer to the buffer containing the sub-folder target language (OpenTM2 language name)
	\param pszEditor pointer to the buffer containing the name of the editor to be used for documents of this sub-folder
	\param pszConversion pointer to the buffer containing the export conversion - currently not in use and should be NULL
	\param pszTranslatorName pointer to the buffer containing the name of the translator
	\param pszTranslatorMail pointer to the buffer containing the translator's mail
	\returns 0 if successful or an error code in case of failures
*/
/*@ADDTOSCRIPTER*/ 
USHORT EqfCreateSubFolder
(
  HSESSION    hSession,                // mand: Eqf session handle
  PSZ         pszParentFolder,         // mand: name of parent (sub)folder
  PSZ         pszSubFolderName,        // mand: subfolders name
  PSZ         pszMemName,              // opt: subfolders Translation Memory or NULL
  PSZ         pszMarkup,               // opt: name of Markup used for subfolder
  PSZ         pszSourceLanguage,       // opt: Source Language used for subfolder or NULL
  PSZ         pszTargetLanguage,       // opt: Target Language used for subfolder or NULL
  PSZ         pszEditor,               // opt: editor used by sub folder  or NULL
  PSZ         pszConversion,           // opt: Conversion used for subfolder or NULL
  PSZ         pszTranslator,           // opt: Name of translator or NULL
  PSZ         pszTranslatorMail        // opt: Mail of translator or NULL
);


/*! \brief Export a folder to the \OTM\Export directory of the specified drive
  \param hSession the session handle returned by the EqfStartSession call
  \param pszFolderName pointer to the buffer containing the name of folder being exported
  \param chTargetDrive folder export target drive
  \param lOptions options for the folder export or 0L
    - DELETE_OPT delete the folder after successful export
    - WITHDICT_OPT add the dictionaries used by the folder
    - WITHMEM_OPT include the folder Translation Memory
    - WITHREADONLYMEM_OPT include the read-only Translation Memory databases
    - WITHDOCMEM_OPT include the Translation Memory databases specified in the document properties
    - OVERWRITE_OPT overwrite any existing exported folder
    - MASTERFOLDER_OPT export as master folder
    - XLIFF_OPT export as XLIFF folder
    - WO_REDUNDANCY_DATA_OPT exclude the redundancy report data of the folder
  \param pszDocuments pointer to the buffer containing the list of documents or NULL to export all documents of the folder
  \param pszDescription pointer to the buffer containing the export description or NULL if not used
  \returns 0 if successful or an error code in case of failures
*/
/*@ADDTOSCRIPTER*/ 
USHORT EqfExportFolder
(
  HSESSION    hSession,                // mand: Eqf session handle
  PSZ         pszFolderName,           // mand: name of folder
  CHAR        chTargetDrive,           // mand: folder target drive
  LONG        lOptions,                // opt: options for the folder export or 0L
                                       // @Contain Memory: {WITHMEM_OPT,WITHREADONLYMEM_OPT,WITHDOCMEM_OPT}
									   // @Other: {DELETE_OPT,WITHDICT_OPT,MASTERFOLDER_OPT, XLIFF_OPT, OVERWRITE_OPT, WO_REDUNDANCY_DATA_OPT }
  PSZ         pszDocuments,            // opt: list of documents or NULL
  PSZ         pszDescription           // opt: export description or NULL
);

/*! \brief Export a folder to the specified directory
  \param hSession the session handle returned by the EqfStartSession call
  \param pszFolderName pointer to the buffer containing the name of folder being exported
  \param pszTargetPath pointer to the buffer containing target directory for the folder export
  \param lOptions options for the folder export or 0L
    - DELETE_OPT delete the folder after successful export
    - WITHDICT_OPT add the dictionaries used by the folder
    - WITHMEM_OPT include the folder Translation Memory
    - WITHREADONLYMEM_OPT include the read-only Translation Memory databases
    - WITHDOCMEM_OPT include the Translation Memory databases specified in the document properties
    - OVERWRITE_OPT overwrite any existing exported folder
    - MASTERFOLDER_OPT export as master folder
    - XLIFF_OPT export as XLIFF folder
    - WO_REDUNDANCY_DATA_OPT exclude the redundancy report data of the folder
  \param pszDocuments pointer to the buffer containing the list of documents or NULL to export all documents of the folder
  \param pszDescription pointer to the buffer containing the export description or NULL if not used
  \returns 0 if successful or an error code in case of failures
*/
/*@ADDTOSCRIPTER*/ 
USHORT EqfExportFolderFP
(
  HSESSION    hSession,                // mand: Eqf session handle
  PSZ         pszFolderName,           // mand: name of folder
  PSZ         pszTargetPath,           // mand: folder target path
  LONG        lOptions,                // opt: options for the folder export or 0L
                                       // @Contain Memory: {WITHMEM_OPT,WITHREADONLYMEM_OPT,WITHDOCMEM_OPT}
									   // @Other: {DELETE_OPT,WITHDICT_OPT,MASTERFOLDER_OPT, XLIFF_OPT, OVERWRITE_OPT, WO_REDUNDANCY_DATA_OPT }
  PSZ         pszDocuments,            // opt: list of documents or NULL
  PSZ         pszDescription           // opt: export description or NULL          
);

/*! \brief Export a folder to the specified directory using a different folder name
  \param hSession the session handle returned by the EqfStartSession call
  \param pszFolderName pointer to the buffer containing the name of folder being exported
  \param pszTargetPath pointer to the buffer containing target directory for the folder export
  \param pszExportAs pointer to the buffer containing name to be use for the exported folder or NULL if not used
  \param lOptions options for the folder export or 0L
    - DELETE_OPT delete the folder after successful export
    - WITHDICT_OPT add the dictionaries used by the folder
    - WITHMEM_OPT include the folder Translation Memory
    - WITHREADONLYMEM_OPT include the read-only Translation Memory databases
    - WITHDOCMEM_OPT include the Translation Memory databases specified in the document properties
    - OVERWRITE_OPT overwrite any existing exported folder
    - MASTERFOLDER_OPT export as master folder
    - XLIFF_OPT export as XLIFF folder
    - WO_REDUNDANCY_DATA_OPT exclude the redundancy report data of the folder
  \param pszDocuments pointer to the buffer containing the list of documents or NULL to export all documents of the folder
  \param pszDescription pointer to the buffer containing the export description or NULL if not used
  \param pszMemoryExportAs comma separated list of new memory names, the first entry is used to rename the folder memory,
           the remaining names are used to rename the search memories
  \returns 0 if successful or an error code in case of failures
*/
/*@ADDTOSCRIPTER*/
USHORT EqfExportFolderFPas
(
  HSESSION    hSession,                // mand: Eqf session handle
  PSZ         pszFolderName,           // mand: name of folder
  PSZ         pszTargetPath,           // mand: folder target path
  PSZ         pszExportAs,             // opt: Export as - optional new name for exported folder
  LONG        lOptions,                // opt: options for the folder export or 0L
                                       // @Contain Memory: {WITHMEM_OPT,WITHREADONLYMEM_OPT,WITHDOCMEM_OPT}
									   // @Other: {DELETE_OPT,WITHDICT_OPT,MASTERFOLDER_OPT, XLIFF_OPT, OVERWRITE_OPT, WO_REDUNDANCY_DATA_OPT }
  PSZ         pszDocuments,            // opt: list of documents or NULL
  PSZ         pszDescription,          // opt: export description or NULL
  PSZ         pszMemoryExportAs        // opt: comma separated list of new memory names, the first entry is used to rename the folder memory, the remaining names are used to rename the search memories
);

/**
 \brief Count the number of words in documents

 This API call counts the words of the documents in a folder or of a subset of
 the documents in a folder.
 The word count report can be a source word count (SOURCE_OPT), a target word count (TARGET_OPT), a 
 duplicate word count (DUPLICATE_OPT), or a memory match word count (TMMATCH_OPT)
 The format of the word count report can be either text format (TEXT_OUTPUT_OPT),
 HTML format (HTML_OUTPUT_OPT), or XML format (XML_OUTPUT_OPT). 

 \param hSession OpenTM2 session handle returned by EqfStartSession
 \param pszFolderName the name of the folder containing the documents being counted
 \param pszDocuments list of documents or NULL if all documents of the folder are to be counted
 \param lOptions options for the word counting
    - TMMATCH_OPT create a memory match word count
    - DUPLICATE_OPT create a duplicates word count
    - SOURCE_OPT create a source word count
    - TARGET_OPT create a target word count
    - FUZZYMATCH_OPT include fuzzy match information in memory match word count 
    - SEPERATEREPLMATCH_OPT count replace matches separately in memory match word count
    - DUPMEMMATCH_OPT include memory match information in duplicates word count 
    - TEXT_OUTPUT_OPT create a plain text word count
    - XML_OUTPUT_OPT create a word count in XML format
    - HTML_OUTPUT_OPT create a word count in HTML format
 \param pszOutFile fully qualified name of the file receiving the word count output
	\returns 0 if successful or an error code
	
**/
/*@ADDTOSCRIPTER*/
USHORT EqfCountWords
(
  HSESSION    hSession,                // mand: Eqf session handle
  PSZ         pszFolderName,           // mand: name of folder
  PSZ         pszDocuments,            // opt: list of documents or NULL
  LONG        lOptions,                // opt: options for the word count
                                       // @Wordount:      TMMATCH_OPT{SEPERATEREPLMATCH_OPT},
									   //                 SOURCE_OPT, TARGET_OPT(default), DUPLICATE_OPT, DUPMEMMATCH_OPT 
                                       // @Output Format: XML_OUTPUT_OPT, HTML_OUTPUT_OPT, TEXT_OUTPUT_OPT(default)
									   // @Other:         {SEPERATEREPLMATCH_OPT,OVERWRITE_OPT}
  PSZ         pszOutFile               // mand: fully qualified output file
);

/*! \brief Import a dictionary
  \param hSession the session handle returned by the EqfStartSession call
  \param pszInFile fully qualified name of input file
  \param pszDictName name of the dictionary
  \param pszPassword password of the dictionary or NULL if not used
  \param lOptions dictionary import options
    one of the format options
    - ASCII_OPT import from SGML (ASCII encoded)
    - ANSI_OPT import from SGML (ANSI encoded)
    - UTF16_OPT import from SGML (Unicode UTF-16 encoded)
    - DXT_UTF8_OPT import from DXT XML (UTF-8 encoded)
    .
    and one of the handling options
    - COMBINE_OPT combine existing entries and imported entries
    - REPLACE_OPT replace existing entries with the and imported entries
    - IGNORE_OPT ignore imported entries when the entry already exists
  \returns 0 if successful or an error code in case of failures
*/
/*@ADDTOSCRIPTER*/
USHORT EqfImportDict
(
  HSESSION    hSession,                // mand: Eqf session handle
  PSZ         pszInFile,               // mand: fully qualified name of input file
  PSZ         pszDictName,             // mand: name of dictionary
  PSZ         pszPassword,             // opt: password of dictionary
  LONG        lOptions                 // opt: dictionary import options
                                       // @Import Mode: ASCII_OPT,ANSI_OPT,DXT_UTF8_OPT,UTF16_OPT(default)
									   // @Merge Mode:  IGNORE_OPT, REPLACE_OPT, COMBINE_OPT
);
/*! \brief Export a dictionary
  \param hSession the session handle returned by the EqfStartSession call
  \param pszDictName name of dictionary
  \param lOptions dictionary export options or 0L
    - OVERWRITE_OPT to overwrite existing files
    .
    and one of the format options
    - ASCII_OPT import from SGML (ASCII encoded)
    - ANSI_OPT import from SGML (ANSI encoded)
    - UTF16_OPT import from SGML (Unicode UTF-16 encoded)
    - DXT_UTF8_OPT import from DXT XML  (UTF-8 encoded)
  \param pszOutFile fully qualified name of output file
  \returns 0 if successful or an error code in case of failures
*/
/*@ADDTOSCRIPTER*/
USHORT EqfExportDict
(
  HSESSION    hSession,                // mand: Eqf session handle
  PSZ         pszDictName,             // mand: name of dictionary
  LONG        lOptions,                // opt: dictionary export options or 0L
                                       // @Export Mode: ASCII_OPT, ANSI_OPT, DXT_UTF8_OPT, UTF16_OPT(default)
                                       // @Other: OVERWRITE_OPT
  PSZ         pszOutFile               // mand: fully qualified name of output file
);
/*! \brief Import a document
  \param hSession the session handle returned by the EqfStartSession call
  \param pszFolderName name of folder receiving the documents
  \param pszFiles list of input files (documents) in form of a comma separated list enclosed in parentheses
  \param pszMemname document Translation Memory or NULL
  \param pszMarkup document markup or NULL
  \param pszEditor document editor or NULL
  \param pszSourceLanguage document source language or NULL
  \param pszTargetLanguage document target language or NULL
  \param pszAlias alias for document name or NULL
  \param pszStartPath optional start path
  \param pszConversion document conversion - not used anymore ans should be NULL
  \param lOptions document import options or 0
         - OVERWRITE_OPT to overwrite any existing document with the imported one 
  \returns 0 if successful or an error code in case of failures
*/
/*@ADDTOSCRIPTER*/
USHORT EqfImportDoc
(
  HSESSION    hSession,                // mand: Eqf session handle
  PSZ         pszFolderName,           // mand: name of folder receiving the documents
  PSZ         pszFiles,                // mand: list of input files (documents)
  PSZ         pszMemname,              // opt: document Translation Memory or NULL
  PSZ         pszMarkup,               // opt: document markup or NULL
  PSZ         pszEditor,               // opt: document editor or NULL
  PSZ         pszSourceLanguage,       // opt: document source language or NULL
  PSZ         pszTargetLanguage,       // opt: document target language or NULL
  PSZ         pszAlias,                // opt: alias for document name or NULL
  PSZ         pszStartPath,            // opt: optional start path
  PSZ         pszConversion,           // opt: optional document conversion
  LONG        lOptions                 // opt: document import options or 0L
                                       // @Option: OVERWRITE_OPT
);


/*! \brief Export a document
  \param hSession the session handle returned by the EqfStartSession call
  \param pszFolderName name of folder receiving the documents
  \param pszFiles list of input files (documents) in form of a comma separated list enclosed in parentheses
  \param pszStartPath optional start path
  \param lOptions document import options or 0
         - OVERWRITE_OPT to overwrite any existing file
         .
         and one of the export format options
         - SOURCE_OPT export the document source file
         - TARGET_OPT export the document target (=translated) file
         - SNOMATCH_OPT export the list of segments with no matching memory proposal
         - VALFORMAT_ODT_OPT export as validation document (ODT format)
         - VALFORMAT_XML_OPT export as validation document (XML format)
         - VALFORMAT_HTML_OPT export as validation document (HTML format)
         - VALFORMAT_DOC_OPT export as validation document (MS DOC format)
         - PLAINXML_OPT export document as plain XML file
         - OPENTM2FORMAT_OPT export the document in the internal OpenTM2 format
         .
         for the validation formats the following two additional options can specified
         - VALFORMAT_COMBINE_OPT combine all documents into a single one
         - VALFORMAT_PROTSEGS_OPT include protected segments in the exported document
         .
         for the SOURCE_OPT, TARGET_OPT, and SNOMATCH_OPT export formats the following relative path options can be used
         - WITHRELATIVEPATH_OPT export the documents with their relative path (this is the default)
         - WITHOUTRELATIVEPATH_OPT export the documents without their relative path
         for the TARGET_OPT export format the following option can be used
         - WITHTRACKID_OPT export the documents with TVT tracking info
  \returns 0 if successful or an error code in case of failures
*/
/*@ADDTOSCRIPTER*/
USHORT EqfExportDoc
(
  HSESSION    hSession,                // mand: Eqf session handle
  PSZ         pszFolderName,           // mand: name of folder
  PSZ         pszFiles,                // mand: list of documents with path information
  PSZ         pszStartPath,            // opt: optional start path
  LONG        lOptions                 // opt: options for document export
                                       // @Export Format: SOURCE_OPT,TARGET_OPT(default),SNOMATCH_OPT, PLAINXML_OPT, OPENTM2FORMAT_OPT,
									   //                 VALFORMAT_XML_OPT{VALFORMAT_COMBINE_OPT  VALFORMAT_PROTSEGS_OPT}, 
									   //                 VALFORMAT_DOC_OPT{VALFORMAT_COMBINE_OPT  VALFORMAT_PROTSEGS_OPT},
									   //                 VALFORMAT_ODT_OPT{VALFORMAT_COMBINE_OPT  VALFORMAT_PROTSEGS_OPT},
									   //                 VALFORMAT_HTML_OPT{VALFORMAT_COMBINE_OPT VALFORMAT_PROTSEGS_OPT},
                                       // @RelativePath: WITHRELATIVEPATH_OPT(default),WITHOUTRELATIVEPATH_OPT
									   // @Other: {VALFORMAT_COMBINE_OPT,VALFORMAT_PROTSEGS_OPT,OVERWRITE_OPT,WITHTRACKID_OPT}
);     






#define VAL_COMBINE_OPT               0x00000001L 
#define VAL_PRESERVE_LINKS_OPT        0x00000002L 
#define VAL_MAN_EXACTMATCH_OPT        0x00000004L
#define VAL_REMOVE_INLINE_OPT         0x00000008L
#define VAL_TRANSTEXT_ONLY_OPT        0x00000010L
#define VAL_INCLUDE_COUNT_OPT         0x00000020L
#define VAL_INCLUDE_MATCH_OPT         0x00000040L
#define VAL_MISMATCHES_ONLY_OPT       0x00000080L

#define VAL_AUTOSUBST_OPT             0x00000100L
#define VAL_MOD_AUTOSUBST_OPT         0x00000200L
#define VAL_EXACT_OPT                 0x00000400L
#define VAL_MOD_EXACT_OPT             0x00000800L
#define VAL_GLOBAL_MEM_OPT            0x00001000L
#define VAL_MACHINE_OPT               0x00002000L
#define VAL_FUZZY_OPT                 0x00004000L
#define VAL_NEW_OPT                   0x00008000L
#define VAL_NOT_TRANS_OPT             0x00010000L
#define VAL_PROTECTED_OPT             0x00020000L
#define VAL_REPLACE_OPT               0x00040000L

#define VAL_VALIDATION_OPT            0x01000000L
#define VAL_PROOFREAD_OPT             0x02000000L


/*! \brief Export a document for validation
  \param hSession the session handle returned by the EqfStartSession call
  \param pszFolderName name of folder receiving the documents
  \param pszFiles list of input files (documents) in form of a comma separated list enclosed in parentheses
  \param pszSavedPath Path to save the exported document
  \param lFormat Exported format type
         - VALFORMAT_XML_OPT  export document in XML format
         - VALFORMAT_HTML_OPT export document in HTML format,it's default.
         - VALFORMAT_DOC_OPT  export document in DOC format
         - VALFORMAT_ODT_OPT  export document in ODT format
         - VALFORMAT_DOCX_OPT export document in DOCX format
  \param lOptions Options for document export validation
         - VAL_COMBINE_OPT              combine exported documents into one,it's invalidated if only one document to export
         - VAL_PRESERVE_LINKS_OPT       preserve links and images
         - VAL_MAN_EXACTMATCH_OPT       detect exact match from manual translation
         - VAL_REMOVE_INLINE_OPT        remove inline tags,set default.
         - VAL_TRANSTEXT_ONLY_OPT       export translates able text only,invalidate if VAL_VALIDATION_OPT set
         - VAL_INCLUDE_COUNT_OPT        include word count info, invalidate if VAL_VALIDATION_OPT set
         - VAL_INCLUDE_MATCH_OPT        include existing match info, invalidate if VAL_VALIDATION_OPT set
         - VAL_MISMATCHES_ONLY_OPT      sub option for VAL_INCLUDE_MATCH_OPT,if applied, lMatchTypes can't be changed,set as (VAL_EXACT_OPT|VAL_MOD_EXACT_OPT|VAL_GLOBAL_MEM_OPT|VAL_MACHINE_OPT|VAL_FUZZY_OPT|VAL_NEW_OPT|VAL_NOT_TRANS_OPT|VAL_REPLACE_OPT)
         - OVERWRITE_OPT                overwrite any existing files
  \param lMatchTypes Include match types in export document
         - VAL_AUTOSUBST_OPT             auto-substitute memory matches
         - VAL_MOD_AUTOSUBST_OPT         modified auto-substitute memory matches
         - VAL_EXACT_OPT                 exact matches
         - VAL_MOD_EXACT_OPT             modified exact matches
         - VAL_GLOBAL_MEM_OPT            global memory matches
         - VAL_MACHINE_OPT               machine translation matches
         - VAL_FUZZY_OPT                 fuzzy matches
         - VAL_NEW_OPT                   new matches
         - VAL_NOT_TRANS_OPT             not translated matches
         - VAL_PROTECTED_OPT             protected matches
         - VAL_REPLACE_OPT               replace matches
  \param lType Export type,one of the following
         - VAL_VALIDATION_OPT           export for validation, it's default. lMatchTypes can't be changed,set as (VAL_AUTOSUBST_OPT|VAL_EXACT_OPT|VAL_MOD_EXACT_OPT|VAL_GLOBAL_MEM_OPT|VAL_MACHINE_OPT|VAL_FUZZY_OPT|VAL_NEW_OPT|VAL_NOT_TRANS_OPT|VAL_REPLACE_OPT)
         - VAL_PROOFREAD_OPT            export for proof reading
  \param pszTranslator Translator name
  \param pszPM Project manager name               
*/
/*@ADDTOSCRIPTER*/
USHORT EqfExportDocVal
(
  HSESSION    hSession,                // mand: Eqf session handle
  PSZ         pszFolderName,           // mand: Name of folder
  PSZ         pszFiles,                // mand: List of documents with path information
  PSZ         pszStartPath,            // opt:  Path to save the exported document
  LONG        lType,                   // opt: export document for validation or proof reading
                                       // @Type: VAL_VALIDATION_OPT(default),VAL_PROOFREAD_OPT
  LONG        lFormat,                 // opt: Exported format type
                                       // @Format: VALFORMAT_XML_OPT,VALFORMAT_HTML_OPT(default),VALFORMAT_DOC_OPT,VALFORMAT_ODT_OPT,VALFORMAT_DOCX_OPT
  LONG        lOptions,                // opt:  Options for document export validation
                                       // @Options: {VAL_COMBINE_OPT,VAL_PRESERVE_LINKS_OPT,VAL_MAN_EXACTMATCH_OPT, VAL_REMOVE_INLINE_OPT(default),
                                       //  VAL_TRANSTEXT_ONLY_OPT,VAL_INCLUDE_COUNT_OPT,VAL_INCLUDE_MATCH_OPT,VAL_MISMATCHES_ONLY_OPT,OVERWRITE_OPT}
  LONG        lMatchTypes,             // opt:  Include match types in export document
                                       // @Match types: {VAL_AUTOSUBST_OPT,VAL_MOD_AUTOSUBST_OPT,VAL_EXACT_OPT,VAL_MOD_EXACT_OPT,
                                       //  VAL_GLOBAL_MEM_OPT,VAL_MACHINE_OPT,VAL_FUZZY_OPT,VAL_NEW_OPT,VAL_NOT_TRANS_OPT,
                                       //  VAL_PROTECTED_OPT,VAL_REPLACE_OPT}

  PSZ     pszTranslator,           // opt: Translator information
  PSZ     pszPM                    // opt: Project manager information
);


/*! \brief Import a Translation Memory
  \param hSession the session handle returned by the EqfStartSession call
  \param pszMemName name of the Translation Memory
  \param pszInFile fully qualified name of the input file
  \param lOptions options for Translation Memory import
         one of the format options 
         - TMX_OPT import in TMX format
         - XLIFF_MT_OPT import in XLIFF format
         - UTF16_OPT import in the EXP format (Unicode UTF-16 encoded)
         - ANSI_OPT import in the EXP format (ANSI encoded)
         - ASCII_OPT import in the EXP format (ASCII encoded)
         .
         and one of the markup table handling functions
         - CANCEL_UNKNOWN_MARKUP_OPT stop import when an unknown markup is detected
         - SKIP_UNKNOWN_MARKUP_OPT skip segments with unknown markup
         - GENERIC_UNKNOWN_MARKUP_OPT use the default markup table for segments with unknown markup
         .
         additional options which can be used
         - CLEANRTF_OPT to remove RTF inline tags (only in combination with TMX_OPT)
         - IGNORE_OPT ignore invalid segments and continue the import 
  \returns 0 if successful or an error code in case of failures
*/
/*@ADDTOSCRIPTER*/
USHORT EqfImportMem
(
  HSESSION    hSession,                // mand: Eqf session handle
  PSZ         pszMemName,              // mand: name of Translation Memory
  PSZ         pszInFile,               // mand: fully qualified name of input file
  LONG        lOptions,                 // opt: options for Translation Memory import
                                       // @Import Mode: TMX_OPT{CLEANRTF_OPT}, XLIFF_MT_OPT,UTF16_OPT,ANSI_OPT,ASCII_OPT(default)
                                       // @Markup Table Handling: CANCEL_UNKNOWN_MARKUP_OPT(default), SKIP_UNKNOWN_MARKUP_OPT, GENERIC_UNKNOWN_MARKUP_OPT
									                     // @Other: {CLEANRTF_OPT,IGNORE_OPT}
                                       
  PSZ         errorBuff,
  ImportStatusDetails*     pImportData
);

/*! \brief Import a Translation Memory (extended version)
  \param hSession the session handle returned by the EqfStartSession call
  \param pszMemName name of the Translation Memory
  \param pszInFile fully qualified name of the input file
  \param pszTM_ID translation memory ID or NULL if not used
  \param pszStoreID ID for the origin of the translation memory or NULL if not used
  \param pszUnused1 not in use, for future enhancements
  \param pszUnused2 not in use, for future enhancements
  \param lOptions options for Translation Memory import
         one of the format options 
         - TMX_OPT import in TMX format
         - XLIFF_MT_OPT import in XLIFF format
         - UTF16_OPT import in the EXP format (Unicode UTF-16 encoded)
         - ANSI_OPT import in the EXP format (ANSI encoded)
         - ASCII_OPT import in the EXP format (ASCII encoded)
         .
         and one of the markup table handling functions
         - CANCEL_UNKNOWN_MARKUP_OPT stop import when an unknown markup is detected
         - SKIP_UNKNOWN_MARKUP_OPT skip segments with unknown markup
         - GENERIC_UNKNOWN_MARKUP_OPT use the default markup table for segments with unknown markup
         .
         additional options which can be used
         - CLEANRTF_OPT to remove RTF inline tags (only in combination with TMX_OPT)
         - IGNORE_OPT ignore invalid segments and continue the import 
         - FORCENEWMATCHID_OPT create a new match segment ID even if the imported match already has one
  \returns 0 if successful or an error code in case of failures
*/
/*@ADDTOSCRIPTER*/
USHORT EqfImportMemEx
(
  HSESSION    hSession,                // mand: Eqf session handle
  PSZ         pszMemName,              // mand: name of Translation Memory
  PSZ         pszInFile,               // mand: fully qualified name of input file
  PSZ         pszTM_ID,                // opt: translation memory ID or NULL if not used
  PSZ         pszStoreID,              // opt: ID for the origin of the translation memory or NULL if not used
  PSZ         pszUnused1,              // opt: not in use, for future enhancements
  PSZ         pszUnused2,              // opt: not in use, for future enhancements
  LONG        lOptions                 // opt: options for Translation Memory import
                                       // @Import Mode: TMX_OPT{CLEANRTF_OPT}, XLIFF_MT_OPT,UTF16_OPT,ANSI_OPT,ASCII_OPT(default)
                                       // @Markup Table Handling: CANCEL_UNKNOWN_MARKUP_OPT(default), SKIP_UNKNOWN_MARKUP_OPT, GENERIC_UNKNOWN_MARKUP_OPT
									                     // @Other: {CLEANRTF_OPT,IGNORE_OPT,FORCENEWMATCHID_OPT}
);

/*! \brief Export a Translation Memory
  \param hSession the session handle returned by the EqfStartSession call
  \param pszMemame name of the Translation Memory
  \param pszOutFile fully qualified name of the output file
  \param lOptions options for Translation Memory export
         - OVERWRITE_OPT to overwrite existing files
         .
         and one of the format options 
         - TMX_OPT import in TMX format
         - XLIFF_MT_OPT import in XLIFF format
         - UTF16_OPT export in the EXP format (Unicode UTF-16 encoded)
         - ANSI_OPT export in the EXP format (ANSI encoded)
         - ASCII_OPT export in the EXP format (ASCII encoded)
         .
         for the TMX_UTF8_OPT and TMX_UTF16_OPT also the following option can be specified
         - TMX_NOCRLF_OPT to remove line breaks within the segment data
\returns 0 if successful or an error code in case of failures
*/
/*@ADDTOSCRIPTER*/
USHORT EqfExportMem
(
  HSESSION    hSession,                // mand: Eqf session handle
  PSZ         pszMemname,              // mand: name of Translation Memory
  PSZ         pszOutFile,              // mand: fully qualified name of output file
  LONG        lOptions                 // opt: options for Translation Memory export
                                       // @Export Mode: UTF16_OPT,ANSI_OPT,TMX_UTF8_OPT{TMX_NOCRLF_OPT},TMX_UTF16_OPT{TMX_NOCRLF_OPT},ASCII_OPT(default)
									   // @Other: OVERWRITE_OPT
);

/*! \brief Organize a Translation Memory
  \param hSession the session handle returned by the EqfStartSession call
  \param pszMemname name of the Translation Memory
  \returns 0 if successful or an error code in case of failures
*/
/*@ADDTOSCRIPTER*/
USHORT EqfOrganizeMem
(
  HSESSION    hSession,                // mand: Eqf session handle
  PSZ         pszMemname               // mand: name of Translation Memory
);

/*! \brief Create a new Translation Memory
  \param hSession the session handle returned by the EqfStartSession call
  \param pszMemname name of the Translation Memory
  \param pszDescription description for new Translation Memory or NULL
  \param chToDrive target drive for new Translation Memory
  \param pszSourceLanguage Translation Memory source language
  \param lOptions type of new Translation Memory
         - LOCAL_TM_OPT create a local memory using the EqfMemoryPlugin
\returns 0 if successful or an error code in case of failures
*/

/*! \brief Create a Initial Translation Memory
    \param hSession the session handle returned by the EqfStartSession call
    \param pszMemName name of the Translation Memory
    \param pszFilePairs list of file pairs as a comma separated list enclosed in parentheses
    \param pszMarkup markup table to be used
    \param pszSGMLMemFile external memory name or NUULL
    \param pszSourceLanguage Translation Memory source language
    \param pszTargetLanguage Translation Memory target language
    \param pszSourceStartPath startpath not stored for source files or NULL
    \param pszTargetStartPath startpath not stored for target files or NULL
    \param lType type of creation
           - NOANA_TYP no analysis is necessary
           - NOTM_TYP no translation memory database
           - PREPARE_TYP only prepare the alignment
    \returns 0 if successful or an error code in case of failures
*/
/*@ADDTOSCRIPTER*/
USHORT EqfCreateITM
(
  HSESSION    hSession,                // mand: Eqf session handle
  PSZ         pszMemName,              // mand: name of new Translation Memory
  PSZ         pszFilePairs,            // opt: list of filepairs or NULL
  PSZ         pszMarkup,               // mand: use markup table
  PSZ         pszSGMLMemFile,          // opt: external memory name or NULL
  PSZ         pszSourceLanguage,       // mand: Translation Memory source language
  PSZ         pszTargetLanguage,       // mand: Translation Memory target language
  PSZ         pszSourceStartPath,      // opt: Startpath not stored for source files or NULL
  PSZ         pszTargetStartPath,      // opt: Startpath not stored for target files or NULL
  LONG        lType                    // opt: type of creation
                                       // @Type:{NOANA_TYP,NOTM_TYP,PREPARE_TYP}
);
// change the machine translation flags
/*! \brief Create a new folder
    \param hSession the session handle returned by the EqfStartSession call
    \param pszMemName name of the Translation Memory
    \param lAction type of action
    - CLEAR_MMOPT clear the machine translation flag
    - SET_MMOPT set the machine translation flag
    \returns 0 if successful or an error code in case of failures
*/
/*@ADDTOSCRIPTER*/
USHORT EqfChangeMFlag
(
  HSESSION    hSession,                // mand: Eqf session handle
  PSZ         pszMemName,              // mand: name of new Translation Memory
  LONG        lAction                  // mand: type of action
                                       // @Action:CLEAR_MMOPT,SET_MMOPT
);

/*! \brief Analyze one or more documents
    \param hSession the session handle returned by the EqfStartSession call
    \param pszFolderName name of folder
    \param pszDocuments comma separated list with document names or NULL to analyze all documents of the folder
    \param pszMemname Translation Memory to be used for the analysis
    \param lOptions analysis options
           - TMMATCH_OPT prepare memory match word count
           - ADDTOMEM_OPT write found proposals to folder/document Translation Memory
           - AUTOSUBST_OPT auto-substitute memory matches
           - UNTRANSLATED_OPT write segments without proposals to an external memory (EXP)
           - AUTOLAST_OPT when more exaxct proposals are available use newest proposal for auto-substitution
           - AUTOJOIN_OPT auto-join segments
           - AUTOCONTEXT_OPT when more exact proposals are available use proposal from same document for auto-substitution
           - REDUNDCOUNT_OPT perform redundancy counting
           - IGNOREPATH_OPT ignore path of document names when looking for exact matches
           - ADJUSTLEADWS_OPT adjust leading white space of auto-substituted segments 
           - ADJUSTTRAILWS_OPT adjust trailing white space of auto-substituted segments 
           - RESPECTCRLF_OPT do not auto-substitute segments when number of line breaks are different
           - NOBLANKATSEGEND_OPT remove blank following a period at the end of the segment
           - NOSUBSTIFIDENTICAL_OPT do not auto-substitute segments when source and target of the proposal is identical
           - PROTECTXMPSCREEN_OPT protect xmp, screen, msgnum, meta, and codeblock sections
           - SENDTOMT_OPT send to / prepare data for MT systems
           - STOPATFIRSTEXACT_OPT stop searching Translation Memory databases at first exact match found
           - IGNORECOMMENTED_OPT ignore memory proposals with comments in the additional info area
           - PROTECTXMP_OPT protect xmp sections
           - PROTECTMSGNUM_OPT protect msgnum sections 
           - PROTECTMETA_OPT protect meta sections
           - PROTECTSCREEN_OPT protect screen sections
           - PROTECTCODEBLOCK_OPT  protect codeblock sections
           - OVERWRITE_OPT overwrite documents in 
    \returns 0 if successful or an error code in case of failures
*/
/*@ADDTOSCRIPTER*/
USHORT EqfAnalyzeDoc
(
  HSESSION    hSession,                // mand: Eqf session handle
  PSZ         pszFolderName,           // mand: name of folder
  PSZ         pszDocuments,            // opt: list with document names or NULL
  PSZ         pszMemname,              // opt: Translation Memory for analysis
  LONG        lOptions                 // opt: options for analysis
                                       //@:{TMMATCH_OPT,ADDTOMEM_OPT,AUTOSUBST_OPT,UNTRANSLATED_OPT,
									   //   AUTOLAST_OPT,AUTOJOIN_OPT,AUTOCONTEXT_OPT,REDUNDCOUNT_OPT,
									   //   OVERWRITE_OPT,IGNOREPATH_OPT,ADJUSTLEADWS_OPT,ADJUSTTRAILWS_OPT,
									   //   NOBLANKATSEGEND_OPT,NOSUBSTIFIDENTICAL_OPT,PROTECTXMPSCREEN_OPT,SENDTOMT_OPT,
									   //   RESPECTCRLF_OPT,STOPATFIRSTEXACT_OPT,IGNORECOMMENTED_OPT}
);

/*! \brief Analyze one or more documents (with additional parameters)
    \param hSession the session handle returned by the EqfStartSession call
    \param pszFolderName name of folder
    \param pszDocuments comma separated list with document names or NULL to analyze all documents of the folder
    \param pszMemname Translation Memory to be used for the analysis
    \param pszProfile analyis profile to be used for the analysis or NULL if not used
    \param pvReserved reserved for future enhancements, has to be NULL
    \param lOptions analysis options
           - TMMATCH_OPT prepare memory match word count
           - ADDTOMEM_OPT write found proposals to folder/document Translation Memory
           - AUTOSUBST_OPT auto-substitute memory matches
           - UNTRANSLATED_OPT write segments without proposals to an external memory (EXP)
           - AUTOLAST_OPT when more exact proposals are available use newest proposal for auto-substitution
           - AUTOJOIN_OPT auto-join segments
           - AUTOCONTEXT_OPT when more exaxct proposals are available use proposal from same document for auto-substitution
           - REDUNDCOUNT_OPT perform redundancy counting
           - IGNOREPATH_OPT ignore path of document names when looking for exact matches
           - ADJUSTLEADWS_OPT adjust leading white space of auto-substituted segments 
           - ADJUSTTRAILWS_OPT adjust trailing white space of auto-substituted segments 
           - RESPECTCRLF_OPT do not auto-substitute segments when number of line breaks are different
           - NOBLANKATSEGEND_OPT remove blank following a period at the end of the segment
           - NOSUBSTIFIDENTICAL_OPT do not auto-substitute segments when source and target of the proposal is identical
           - PROTECTXMPSCREEN_OPT protect xmp, screen, msgnum, meta, and codeblock sections
           - SENDTOMT_OPT send to / prepare data for MT systems
           - STOPATFIRSTEXACT_OPT stop searching Translation Memory databases at first exact match found
           - IGNORECOMMENTED_OPT ignore memory proposals with comments in the additional info area
           - PROTECTXMP_OPT protect xmp sections
           - PROTECTMSGNUM_OPT protect msgnum sections 
           - PROTECTMETA_OPT protect meta sections
           - PROTECTSCREEN_OPT protect screen sections
           - PROTECTCODEBLOCK_OPT  protect codeblock sections
           - OVERWRITE_OPT overwrite documents in 
    \returns 0 if successful or an error code in case of failures
*/
/*@ADDTOSCRIPTER*/
USHORT EqfAnalyzeDocEx
(
  HSESSION    hSession,                // mand: Eqf session handle
  PSZ         pszFolderName,           // mand: name of folder
  PSZ         pszDocuments,            // opt: list with document names or NULL
  PSZ         pszMemname,              // opt: Translation Memory for analysis
  PSZ         pszProfile,              // opt: analyis profile name or NULL
  PSZ         pszMTOutputOptions,      // opt: MT output file options, this parameter consists of a list of MT output file names (NOMATCH,ALLSEGS,ALLWMATCH,ALLWMATCHSOURCE,NOPROPOSAL,XLIFF) followed
                                       //  by the options in parenthesis, format options: TMX, EXP, XML, filter options: HAMSTER, NOHAMSTER, MACHINEMATCH, NOMACHINEMATCH, NOFUZZYABOVE=n, duplicates options: DUPLICATES,
                                       //  NODUPLICATES, word count options: WORDCOUNT, NOWORDCOUNT 
  LONG        lOptions                 // opt: options for analysis
                                       //@:{AUTOSUBST_OPT,AUTOLAST_OPT,AUTOJOIN_OPT,AUTOCONTEXT_OPT}
                                       //@:{ADDTOMEM_OPT,ADJUSTLEADWS_OPT,ADJUSTTRAILWS_OPT,TMMATCH_OPT}
                                       //@:{UNTRANSLATED_OPT,NOBLANKATSEGEND_OPT,NOSUBSTIFIDENTICAL_OPT,PROTECTXMPSCREEN_OPT}
                                       //@:{STOPATFIRSTEXACT_OPT,SENDTOMT_OPT,RESPECTCRLF_OPT,REDUNDCOUNT_OPT}
                                       //@:{OVERWRITE_OPT,IGNOREPATH_OPT,IGNORECOMMENTED_OPT}
);
/*! \brief Delete a Translation Memory
    \param hSession the session handle returned by the EqfStartSession call
    \param pszMemName name of the memory being deleted
    \returns 0 if successful or an error code in case of failures
*/
/*@ADDTOSCRIPTER*/
USHORT EqfDeleteMem
(
  HSESSION    hSession,                // mand: Eqf session handle
  PSZ         pszMemName               // mand: Translation Memory being deleted
);

/*! \brief Import a folder from the \OTM\EXPORT directory
    \param hSession the session handle returned by the EqfStartSession call
    \param pszFolderName name of the folder being imported
    \param chFromDrive drive containing the imported folder
    \param chToDrive target drive for imported folder
    \param lOptions folder import options
           - XLIFF_OPT import a XLIFF folder (when not specified the import of a standard FXP folder is assumed)
           - NOMARKUP_UPDATE_OPT do not import any markup tables contained in the exported folder
           - WITHDICT_OPT import any dictionaries contained in the exported folder
           - WITHMEM_OPT  import any Translation Memory databases contained in the exported folder
    \returns 0 if successful or an error code in case of failures
*/
/*@ADDTOSCRIPTER*/
USHORT EqfImportFolder
(
  HSESSION    hSession,                // mand: Eqf session handle
  PSZ         pszFolderName,           // mand: name of folder being imported
  CHAR        chFromDrive,             // mand: drive containing the imported folder
  CHAR        chToDrive,               // opt: target drive for folder
  LONG        lOptions                 // opt: folder import options
                                       // @Import Mode: XLIFF_OPT
									   // @Other: {WITHDICT_OPT, WITHMEM_OPT}
);
/*! \brief Import a folder from the given directory
    \param hSession the session handle returned by the EqfStartSession call
    \param pszFolderName name of the folder being imported
    \param pszFromPath the fully qualified path name of the directory containing the imported folder
    \param chToDrive target drive for imported folder
    \param lOptions folder import options
           - XLIFF_OPT import a XLIFF folder (when not specified the import of a standard FXP folder is assumed)
           - NOMARKUP_UPDATE_OPT do not import any markup tables contained in the exported folder
           - WITHDICT_OPT import any dictionaries contained in the exported folder
           - WITHMEM_OPT  import any Translation Memory databases contained in the exported folder
    \returns 0 if successful or an error code in case of failures
*/
/*@ADDTOSCRIPTER*/
USHORT EqfImportFolderFP
(
  HSESSION    hSession,                // mand: Eqf session handle
  PSZ         pszFolderName,           // mand: name of folder being imported
  PSZ         pszFromPath,             // mand: path containing the imported folder
  CHAR        chToDrive,               // opt: target drive for folder
  LONG        lOptions                 // opt: folder import options
                                       // @Import Mode: XLIFF_OPT
									   // @Other: {WITHDICT_OPT, WITHMEM_OPT}
);

/*! \brief Import a folder from the given directory
    \param hSession the session handle returned by the EqfStartSession call
    \param pszFolderName name of the folder being imported
    \param pszFromPath the fully qualified path name of the directory containing the imported folder
    \param chToDrive target drive for imported folder
    \param pszNewFolderName new name for the folder after the import
    \param lOptions folder import options
           - XLIFF_OPT import a XLIFF folder (when not specified the import of a standard FXP folder is assumed)
           - NOMARKUP_UPDATE_OPT do not import any markup tables contained in the exported folder
           - WITHDICT_OPT import any dictionaries contained in the exported folder
           - WITHMEM_OPT  import any Translation Memory databases contained in the exported folder
    \returns 0 if successful or an error code in case of failures
*/
/*@ADDTOSCRIPTER*/
USHORT EqfImportFolderAs
(
  HSESSION    hSession,                // mand: Eqf session handle
  PSZ         pszFolderName,           // mand: name of folder being imported
  PSZ         pszFromPath,             // mand: path containing the imported folder
  CHAR        chToDrive,               // opt: target drive for folder
  PSZ         pszNewFolderName,        // opt: new name for the folder after the import
  LONG        lOptions                 // opt: folder import options
                                       // @Import Mode: XLIFF_OPT
									   // @Other: {WITHDICT_OPT, WITHMEM_OPT}
);

/*! \brief Import a folder from the given directory
    \param hSession the session handle returned by the EqfStartSession call
    \param pszFolderName name of the folder being imported
    \param pszFromPath the fully qualified path name of the directory containing the imported folder
    \param chToDrive target drive for imported folder
    \param pszNewFolderName new name for the folder after the import
    \param pszNewMemNames comma separated list of new memory names, the first entry is used to rename the folder memory,
           the remaining names are used to rename the search memories
    \param lOptions folder import options
           - XLIFF_OPT import a XLIFF folder (when not specified the import of a standard FXP folder is assumed)
           - NOMARKUP_UPDATE_OPT do not import any markup tables contained in the exported folder
           - WITHDICT_OPT import any dictionaries contained in the exported folder
           - WITHMEM_OPT  import any Translation Memory databases contained in the exported folder
    \returns 0 if successful or an error code in case of failures
*/
/*@ADDTOSCRIPTER*/
USHORT EqfImportFolderAs2
(
  HSESSION    hSession,                // mand: Eqf session handle
  PSZ         pszFolderName,           // mand: name of folder being imported
  PSZ         pszFromPath,             // mand: path containing the imported folder
  CHAR        chToDrive,               // opt: target drive for folder
  PSZ         pszNewFolderName,        // opt: new name for the folder after the import
  PSZ         pszNewMemNames,          // opt: comma separated list of new memory names, the first entry is used to rename the folder memory, the remaining names are used to rename the search memories
  LONG        lOptions                 // opt: folder import options
                                       // @Import Mode: XLIFF_OPT
									   // @Other: {WITHDICT_OPT, WITHMEM_OPT}
);


/*! \brief Delete a folder
    \param hSession the session handle returned by the EqfStartSession call
    \param pszFolderName name of the folder being deleted
    \returns 0 if successful or an error code in case of failures
*/
/*@ADDTOSCRIPTER*/
USHORT EqfDeleteFolder
(
  HSESSION    hSession,                // mand: Eqf session handle
  PSZ         pszFolderName            // mand: name of folder being deleted
);


/*! \brief Get the properties of a folder
    \param hSession the session handle returned by the EqfStartSession call
    \param pszFolderName name of the folder to get the properties from
    \param pExtFolProp pointer to a EXTFOLPROP buffer receiving the properties of the folder on return
    \returns 0 if successful or an error code in case of failures
*/
/*@ADDTOSCRIPTER*/
USHORT EqfGetFolderProp
(
  HSESSION    hSession,                // mand: Eqf session handle
  PSZ         pszFolderName,           // mand: name of folder to get properties from
  PEXTFOLPROP pExtFolProp              // mand: structure of Folderproperties to be returned
);

/*! \brief Get a specific value from the properties of a folder
    \param hSession the session handle returned by the EqfStartSession call
    \param pszFolderName name of the folder to get the property value from
    \param pszKey name of the value to be retrieved
    \param pszBuffer pointer to a buffer area receiving the folder property value 
    \param iBufSize size of the buffer in number of bytes
    \returns 0 if successful or an error code in case of failures
*/
/*@ADDTOSCRIPTER*/
USHORT EqfGetFolderPropEx
(
  HSESSION    hSession,                // mand: Eqf session handle
  PSZ         pszFolderName,           // mand: name of the folder to get the property value from
  PSZ         pszKey,                  // mand: name of the requested value
                                       //@: DRIVE,TARGETLANGUAGE,SOURCELANGUAGE,MEMORY,DICTIONARIES,ROMEMORIES,DESCRIPTION,ANALYSISPROFILE,COUNTINGPROFILE,SHIPMENT
  PSZ         pszBuffer,               // mand: @API: buffer for the returned value @Scripter: name of the variable receiving the requested value
  int         iBufSize                 // /*@Ignore*/ mand: size of the buffer
);


/*! \brief Delete one or more documents
    \param hSession the session handle returned by the EqfStartSession call
    \param pszFolderName name of the folder containing the documents
    \param pszDocuments a comma separeted list of documents being deleted
    \returns 0 if successful or an error code in case of failures
*/
/*@ADDTOSCRIPTER*/
USHORT EqfDeleteDoc
(
  HSESSION    hSession,                // mand: Eqf session handle
  PSZ         pszFolderName,           // mand: name of folder containing the documents
  PSZ         pszDocuments             // mand: list of documents being deleted
);


/*! \brief Create a counting report
    \param hSession the session handle returned by the EqfStartSession call
    \param pszFolderName name of the folder containing the documents
    \param pszDocuments comma separeted list of documents being counted or NULL if all documents of the folder should be counted
    \param pszOutFile fully qualified name of the output file
    \param usReport ID of the report being created
           - HISTORY_REP create a history report
           - COUNTING_REP create a counting report
           - CALCULATING_REP create a calculating report
           - PREANALYSIS_REP create a pre-analysis report
           - REDUNDANCY_REP create a redundancy report
           - REDUNDANCYSEGMENT_REP create a redundant segment list
    \param usType type of the report being created
           valid for a history report are
           - BRIEF_SORTBYDATE_REPTYPE create a brief report sorted by date
           - BRIEF_SORTBYDOC_REPTYPE create a brief report sorted by documents
           - DETAIL_REPTYPE create a detailed report
           valid types for counting report
           - WITHTOTALS_REPTYPE counting report with totals
           - WITHOUTTOTALS_REPTYPE counting report without totals
           valid types for calculating report, pre-analysis report, redundancy report, and redundant segment list
           - BASE_REPTYPE only base 
           - BASE_SUMMARY_REPTYPE only summary 
           - BASE_SUMMARY_FACTSHEET_REPTYPE base, summary, and factsheet
           - SUMMARY_FACTSHEET_REPTYPE only summary and factsheet
           - FACTSHEET_REPTYPE only factsheet
    \param pszProfile name of the counting report profile to be applied
    \param lOptions options for the counting report
           - OVERWRITE_OPT overwrite any existing output file
           .
           one of the output format options
           - TEXT_OUTPUT_OPT create a plain text report
           - XML_OUTPUT_OPT create a XML report
           - HTML_OUTPUT_OPT create a HTML report
    \returns 0 if successful or an error code in case of failures
*/
/*@ADDTOSCRIPTER*/
USHORT EqfCreateCountReport
(
  HSESSION    hSession,                // mand: Eqf session handle
  PSZ         pszFolderName,           // mand: name of folder containing the documents
  PSZ         pszDocuments,            // opt: list of documents being counted
  PSZ         pszOutFile,              // mand: fully qualified name of output file
  USHORT      usReport,                // mand: ID of report being created
                                       // @Report ID:CALCULATING_REP,PREANALYSIS_REP,REDUNDANCY_REP,REDUNDANCYSEGMENT_REP
  USHORT      usType,                  // mand: type of report being created
                                       // @Type:BASE_REPTYPE,BASE_SUMMARY_REPTYPE,BASE_SUMMARY_FACTSHEET_REPTYPE,SUMMARY_FACTSHEET_REPTYPE,FACTSHEET_REPTYPE
  PSZ         pszProfile,              // opt: name of profile
  LONG        lOptions                 // opt: output format
                                       // @Output Format: HTML_OUTPUT_OPT, XML_OUTPUT_OPT,TEXT_OUTPUT_OPT(default)
									   // @Other: OVERWRITE_OPT
);

/*! \brief Create a counting report
    \param hSession the session handle returned by the EqfStartSession call
    \param pszFolderName name of the folder containing the documents
    \param pszDocuments comma separeted list of documents being counted or NULL if all documents of the folder should be counted
    \param pszOutFile fully qualified name of the output file
    \param usReport ID of the report being created
           - HISTORY_REP create a history report
           - COUNTING_REP create a counting report
           - CALCULATING_REP create a calculating report
           - PREANALYSIS_REP create a pre-analysis report
           - REDUNDANCY_REP create a redundancy report
           - REDUNDANCYSEGMENT_REP create a redundant segment list
    \param usType type of the report being created
           valid for a history report are
           - BRIEF_SORTBYDATE_REPTYPE create a brief report sorted by date
           - BRIEF_SORTBYDOC_REPTYPE create a brief report sorted by documents
           - DETAIL_REPTYPE create a detailed report
           valid types for counting report
           - WITHTOTALS_REPTYPE counting report with totals
           - WITHOUTTOTALS_REPTYPE counting report without totals
           valid types for calculating report, pre-analysis report, redundancy report, and redundant segment list
           - BASE_REPTYPE only base 
           - BASE_SUMMARY_REPTYPE only summary 
           - BASE_SUMMARY_FACTSHEET_REPTYPE base, summary, and factsheet
           - SUMMARY_FACTSHEET_REPTYPE only summary and factsheet
           - FACTSHEET_REPTYPE only factsheet
    \param pszProfile name of the counting report profile to be applied
    \param pszShipment shipment number or one of the keywords "All Shipments" or "Single Shipments"
    \param pszUnused1 for future enhancements, currently unused
    \param pszUnused2 for future enhancements, currently unused
    \param lOptions options for the counting report
           - OVERWRITE_OPT overwrite any existing output file
           .
           one of the output format options
           - TEXT_OUTPUT_OPT create a plain text report
           - XML_OUTPUT_OPT create a XML report
           - HTML_OUTPUT_OPT create a HTML report
    \returns 0 if successful or an error code in case of failures
*/
/*@ADDTOSCRIPTER*/
USHORT EqfCreateCountReportEx
(
  HSESSION    hSession,                // mand: Eqf session handle
  PSZ         pszFolderName,           // mand: name of folder containing the documents
  PSZ         pszDocuments,            // opt: list of documents being counted
  PSZ         pszOutFile,              // mand: fully qualified name of output file
  USHORT      usReport,                // mand: ID of report being created
                                       // @Report ID:CALCULATING_REP,PREANALYSIS_REP,REDUNDANCY_REP,REDUNDANCYSEGMENT_REP
  USHORT      usType,                  // mand: type of report being created
                                       // @Type:BASE_REPTYPE,BASE_SUMMARY_REPTYPE,BASE_SUMMARY_FACTSHEET_REPTYPE,SUMMARY_FACTSHEET_REPTYPE,FACTSHEET_REPTYPE
  PSZ         pszProfile,              // opt: name of profile
  PSZ         pszShipment,             // opt: shipment number or one of the keywords "All Shipments" or "Single Shipments"
  PSZ         pszUnused1,              // opt: for future enhancements, currently unused
  PSZ         pszUnused2,              // opt: for future enhancements, currently unused
  LONG        lOptions                 // opt: output format
                                       // @Output Format: HTML_OUTPUT_OPT, XML_OUTPUT_OPT,TEXT_OUTPUT_OPT(default)
									   // @Other: OVERWRITE_OPT
);

/*! \brief Create a archive memory from translated documents
    \param hSession the session handle returned by the EqfStartSession call
    \param pszFolderName name of the folder
    \param chToDrive folder drive, can be ignored
    \param pszDocuments comma separated list with document names or NULL to include all folder documents
    \param pszMemname name of output Translation Memory
    \param lOptions options for archive memory function
           - OVERWRITE_OPT delete all existing proposals in the Translation Memory before starting
           - USEASFOLDERTM_OPT use specified Translation Memory as folder memory
           - SOURCESOURCEMEM_OPT create a source-source Translation Memory
           - SETMFLAG_OPT set machine translation flag in the proposals written to the Translation Memory
    \returns 0 if successful or an error code in case of failures
*/
/*@ADDTOSCRIPTER*/
USHORT EqfArchiveTM
(
  HSESSION    hSession,                // mand: Eqf session handle
  PSZ         pszFolderName,           // mand: name of folder
  CHAR        chToDrive,               // opt: drive
  PSZ         pszDocuments,            // opt: list with document names or NULL
  PSZ         pszMemname,              // mand: output Translation Memory
  LONG        lOptions                 // opt: options for analysis
                                       // @Options: {USEASFOLDERTM_OPT,SOURCESOURCEMEM_OPT,SETMFLAG_OPT,OVERWRITE_OPT}
);
/*! \brief Create a internal markup table (.TBL) from an external markup table (.TBX)
    \param hSession the session handle returned by the EqfStartSession call
    \param pszInFile fully qualified name of input file (.TBX format)
    \param pszOutFile fully qualified name of output file (.TBL format)
    \returns 0 if successful or an error code in case of failures
*/
/*@ADDTOSCRIPTER*/
USHORT EqfCreateMarkup
(
  HSESSION    hSession,                // mand: Eqf session handle
  PSZ         pszInFile,               // mand: fully qualified name of input file
  PSZ         pszOutFile               // mand: fully qualified name of output file
);

/*! \brief Start a OpenTM2 API call session
    \param phSession pointer to a buffer receiving the session handle
    \returns 0 if successful or an error code in case of failures
*/
/*@ADDTOSCRIPTER*/
USHORT EqfStartSession
(
  PHSESSION   phSession                // mand: ptr to callers Eqf session handle variable
);

/*! \brief End a OpenTM2 API call session
    \param hSession the session handle returned by the EqfStartSession call
    \returns 0 if successful or an error code in case of failures
*/
/*@ADDTOSCRIPTER*/
USHORT EqfEndSession
(
  HSESSION    hSession                 // mand: Eqf session handle
);

/*! \brief Get information about the last occured error
    \param hSession the session handle returned by the EqfStartSession call
    \param pusRC pointer to the buffer for last return code
    \param pszMsgBuffer pointer to a buffer receiving the error message text 
    \param usBufSize size of message buffer in number of bytes
    \returns 0 if successful or an error code in case of failures
*/
USHORT EqfGetLastError
(
  HSESSION    hSession,                // Eqf session handle
  PUSHORT     pusRC,                   // ptr to buffer for last return code
  PSZ         pszMsgBuffer,            // ptr to buffer receiving the message
  USHORT      usBufSize                // size of message buffer in bytes
);
/*! \brief Get information about the last occured error (in UTF16 encoding)
    \param hSession the session handle returned by the EqfStartSession call
    \param pusRC pointer to the buffer for last return code
    \param pszMsgBuffer pointer to a buffer receiving the error message text (
    \param usBufSize size of message buffer in number of characters
    \returns 0 if successful or an error code in case of failures
*/
USHORT EqfGetLastErrorW
(
  HSESSION    hSession,                // Eqf session handle
  PUSHORT     pusRC,                   // ptr to buffer for last return code
  wchar_t    *pszMsgBuffer,            // ptr to buffer receiving the message
  USHORT      usBufSize                // size of message buffer in bytes
);


// 
/*! \brief Create a counting report (old interface, please use EqfCreateCountReport instead)
    \param hSession the session handle returned by the EqfStartSession call
    \param chDriveLetter drive letter of the folder location, not used anymore and should be empty
    \param pszFolderName name of the folder
    \param pszDocuments comma separated list of document names or NULL if complete folder should be counted
    \param pReportType pointer to a REPORTTYPE structure containing the report type information
    \param pszOutfileName fully qualified name of the output report file
    \param pszFormat format of the output file
           - "ASCII" for a plain text report
           - "HTML" for a HTML report
           - "RTF" for a RTF report
           - "XML" for a XML report
    \param pszProfile name of the calculation profile to be used, when specified the following parameters are not used and
           all information is retrieved from the profile instead
    \param pRepSettings pointer to a REPORTSETTINGS structure containing the report settings
    \param pFactSheet pointer to a FACTSHEET structure containing the factsheet infos
    \param usColumn number of columns to in the report
    \param usCategory number of categories in the report
    \param pFinalFactors pointer to a FINALFACTORS structure containing the payment factors
    \param lOptSecurity security check level
    \param bSingleShipment 1 = count single shipments, 0 = count all shipments
    \returns 0 if successful or an error code in case of failures
*/
/*@ADDTOSCRIPTER*/
USHORT EqfCreateCntReport
(
  HSESSION    hSession,                // mand: Eqf session handle
  CHAR        chDriveLetter,           // opt: target drive letter
  PSZ         pszFolderName,           // mand: name of folder containing the documents
  PSZ         pszDocuments,            // opt: list of documents being counted
  PREPORTTYPE pReportType,             // mand: type of report
  PSZ         pszOutfileName,              // mand: fully qualified name of output file
  PSZ         pszFormat,               // mand: outpur format
  PSZ         pszProfile,              // opt: name of profile
  PREPORTSETTINGS pRepSettings,        // mand: report settings
  PFACTSHEET pFactSheet,               // mand: factsheet settings
  USHORT      usColumn,                // mand: column handling
  USHORT      usCategory,              // mand: category setting
  PFINALFACTORS pFinalFactors,         // mand: final factors
  LONG        lOptSecurity,            // opt: security settings 
                                       // @Security:{PLAUS_OPT,LOST_OPT,LIST_OPT}
  BOOL        bSingleShipment          // opt: shipment handlign
);

/*! \brief Create a counting report (old interface, please use EqfCreateCountReport instead)
    \param hSession the session handle returned by the EqfStartSession call
    \param chDriveLetter drive letter of the folder location, not used anymore and should be empty
    \param pszFolderName name of the folder
    \param pszDocuments comma separated list of document names or NULL if complete folder should be counted
    \param pReportType pointer to a REPORTTYPE structure containing the report type information
    \param pszOutfileName fully qualified name of the output report file
    \param pszFormat format of the output file
           - "ASCII" for a plain text report
           - "HTML" for a HTML report
           - "RTF" for a RTF report
           - "XML" for a XML report
    \param pszProfile name of the calculation profile to be used, when specified the following parameters are not used and
           all information is retrieved from the profile instead
    \param pRepSettings pointer to a REPORTSETTINGS structure containing the report settings
    \param pFactSheet pointer to a FACTSHEET structure containing the factsheet infos
    \param usColumn number of columns to in the report
    \param usCategory number of categories in the report
    \param pFinalFactors pointer to a FINALFACTORS structure containing the payment factors
    \param lOptSecurity security check level
    \param pszShipment shipment number or one of the keywords "All Shipments" or "Single Shipments"
    \param pszUnused1 for future enhancements, currently unused
    \param pszUnused2 for future enhancements, currently unused
    \returns 0 if successful or an error code in case of failures
*/
USHORT EqfCreateCntReportEx
(
  HSESSION    hSession,                // mand: Eqf session handle
  CHAR        chDriveLetter,           // opt: target drive letter
  PSZ         pszFolderName,           // mand: name of folder containing the documents
  PSZ         pszDocuments,            // opt: list of documents being counted
  PREPORTTYPE pReportType,             // mand: type of report
  PSZ         pszOutfileName,              // mand: fully qualified name of output file
  PSZ         pszFormat,               // mand: outpur format
  PSZ         pszProfile,              // opt: name of profile
  PREPORTSETTINGS pRepSettings,        // mand: report settings
  PFACTSHEET pFactSheet,               // mand: factsheet settings
  USHORT      usColumn,                // mand: column handling
  USHORT      usCategory,              // mand: category setting
  PFINALFACTORS pFinalFactors,         // mand: final factors
  LONG        lOptSecurity,            // opt: security settings 
                                       // @Security:{PLAUS_OPT,LOST_OPT,LIST_OPT}
  PSZ pszShipment,                     // opt: shipment number or one of the keywords "All Shipments" or "Single Shipments"
  PSZ pszUnused1,                      // opt: for future enhancements, currently unused
  PSZ pszUnused2                       // opt: for future enhancements, currently unused
);



/*! \brief Load a segmented document into memory 
    \param hSession the session handle returned by the EqfStartSession call
    \param pszFullDocName fully qualified name of segmented document
    \param hLoadedFile pointer to buffer for handle of loaded file
    \returns 0 if successful or an error code in case of failures
*/
USHORT EqfLoadSegFile
(
  HSESSION    hSession,                // Eqf session handle
  PSZ         pszFullDocName,          // fully qualified name of segmented document
  HPARSSEGFILE *phLoadedFile           // pointer to buffer for handle of loaded file
);

/*! \brief Get number of segments in loaded file
    \param hLoadedFile the loaded file handle returned by the EqfLoadSegFile call
    \param plNumOfSegs pointer to a buffer receiving the number of segments in the loaded file
    \returns 0 if successful or an error code in case of failures
*/
USHORT EqfGetSegNum
(
  HPARSSEGFILE hLoadedFile,            // handle of loaded segmented file
  PLONG       plNumOfSegs              // pointer to buffer for number of segments in file
);

/*! \brief Free all memory occupied by a loaded file
    \param hLoadedFile the loaded file handle returned by the EqfLoadSegFile call
    \returns 0 if successful or an error code in case of failures
*/
USHORT EqfFreeSegFile
(
  HPARSSEGFILE hLoadedFile             // handle of loaded segmented file
);

// write a segmented document to disk
/*! \brief Create a new folder
    \param hLoadedFile the loaded file handle returned by the EqfLoadSegFile call
    \param pszFullDocName fully qualified name of the segmented document file
    \returns 0 if successful or an error code in case of failures
*/
USHORT EqfWriteSegFile
(
  HPARSSEGFILE hLoadedFile,            // handle of loaded segmented file
  PSZ         pszFullDocName           // fully qualified name of segmented document
);

/*! \brief Get the data of the specified segment
    \param hLoadedFile the loaded file handle returned by the EqfLoadSegFile call
    \param lSegNum number of the segment
    \param pSeg pointer to a PARSSEGMENTW structure receiving the segment data
    \returns 0 if successful or an error code in case of failures
*/
USHORT EqfGetSegW
(
  HPARSSEGFILE  hSegFile,              // handle of loaded segmented file
  LONG          lSegNum,               // number of requested segment
  PPARSSEGMENTW pSeg                   // ptr to buffer for segment data
);

/*! \brief Update the data of a specific segment
    \param hLoadedFile the loaded file handle returned by the EqfLoadSegFile call
    \param lSegNum number of the segment
    \param pSeg pointer to a PARSSEGMENTW structure containing the new segment data
    \returns 0 if successful or an error code in case of failures
*/
USHORT EqfUpdateSegW
(
  HPARSSEGFILE hSegFile,               // handle of loaded segmented file
  LONG         lSegNum,                // number of segment to update
  PPARSSEGMENTW pSeg                   // ptr new segment data
);

/*! \brief Construct the fully qualified name of a segmented document from long folder name and document name
    \param hSession the session handle returned by the EqfStartSession call
    \param pszFolderName pointer to name of the folder
    \param pszDocumentName pointer to document name
    \param fSource when TRUE the name of the segmented source file name is constructed, when FALSE the name of the 
      segmented target file name is constructed
    \param pszSegFile points to buffer receiving the fully qualified document name
    \returns 0 if successful or an error code in case of failures
*/
/*@ADDTOSCRIPTER*/
USHORT EqfBuildSegDocName
(
  HSESSION         hSession,           // mand: non-DDE session handle
  PSZ              pszFolderName,      // mand: pointer to long folder name w/p drive, path and ext
  PSZ              pszDocumentName,    // mand: pointer to long document name
  USHORT           fSource,            // mand: TRUE (1)  = build segmented source file name
                                       //       FALSE (0) = build segmented target file name
  PSZ              pszSegFile          // mand: points to buffer for full file name
                                       //       must have a size of at least 60 characters
);

/*! \brief Set the default target language (aka system language)
    \param hSession the session handle returned by the EqfStartSession call
    \param pSystemPropLang the new system language (OpenTM2 language name)
    \returns 0 if successful or an error code in case of failures
*/
/*@ADDTOSCRIPTER*/
USHORT EqfSetSysLanguage
(
  HSESSION    hSession,                // mand: ptr to callers Eqf session handle variable
  PSZ         pSystemPropLang          // mand: System language to be set
);

/*! \brief Get the default target language (aka system language)
    \param hSession the session handle returned by the EqfStartSession call
    \param pSystemPropLang buffer receiving the actual system language (OpenTM2 language name)
    \returns 0 if successful or an error code in case of failures
*/
/*@ADDTOSCRIPTER*/
USHORT EqfGetSysLanguage
(
  HSESSION   hSession,                // mand: callers Eqf session handle variable
  PSZ        pSystemPropLang          // mand: System language filled at output
);

/*! \brief Get the progress of currently running process
    \param hSession the session handle returned by the EqfStartSession call
    \param pusProgress pointer to a buffer receiving the current progress value
    \returns 0 if successful or an error code in case of failures
*/
USHORT EqfGetProgress
(
  HSESSION   hSession,                // callers Eqf session handle variable
  PUSHORT    pusProgress              // pointer to buffer for current progress value
);

/*! \brief Get the line information for a specific segment
    \param hSession the session handle returned by the EqfStartSession call
    \param lSegNum number of the requested segment
    \param plStartLine points to a buffer for the segment start line
    \param plEndLine points to a buffer for the segment end line
    \returns 0 if successful or an error code in case of failures
*/
USHORT EqfGetSourceLine
(
  HPARSSEGFILE hLoadedFile,           // handle of loaded segmented file
  LONG         lSegNum,               // number of requested segment
  PLONG        plStartLine,           // points to buffer for segment start line
  PLONG        plEndLine              // points to buffer for segment end line
);

/*! \brief Get the segment number for a given line/column position
    \param hSession the session handle returned by the EqfStartSession call
    \param lLine line position of segment
    \param lColumn columns position of segment
    \param plSegNum number of segment found at given position
    \returns 0 if successful or an error code in case of failures
*/
USHORT EqfGetSegmentNumber
(
  HPARSSEGFILE hLoadedFile,           // handle of loaded segmented file
  LONG          lLine,                 // line position of segment
  LONG          lColumn,               // columns position of segment
  PLONG         plSegNum               // number of segment found at given position
);



/*! \brief Structure containing the segment or memory match information
     This structure is used by the EqfGetMatchLevel API for the segment from the
     document and for the memory proposal
*/
//#pragma pack( push, TM2StructPacking, 1 )
typedef struct _EQFSEGINFO
{
  WCHAR           szSource[EQF_SEGLEN];          // segment source text (UTF-16 encoded)
  WCHAR           szTarget[EQF_SEGLEN];          // segment target text (UTF-16 encoded) (empty for document segment)
  LONG            lSegNumber;                    // segment number
  CHAR            szDocument[MAX_LONGFILESPEC];  // name of document
  CHAR            szSourceLanguage[MAX_LANG_LENGTH];   // source language of segment
  CHAR            szTargetLanguage[MAX_LANG_LENGTH];   // target language of segment
  CHAR            szMarkup[MAX_FILESPEC];        // markup of segment
} EQFSEGINFO, *PEQFSEGINFO;
//#pragma pack( pop, TM2StructPacking )

//
// options for EqfGetMatchLevel API
//

// suppress generic inline tag replacement
#define NO_GENERIC_INLINETAG_REPL_OPT    0x0001

// use generic inline tag replacement function
#define USE_GENERIC_INLINETAG_REPL_OPT   0x0002

/*! \brief State/type of matches used by EqfGetMatchLevel API
*/
typedef enum _EQFMATCHSTATE
{
  REPLACE_MATCHSTATE,                            // replace match
  FUZZYREPLACE_MATCHSTATE,                       // fuzzy replace match
  FUZZY_MATCHSTATE,                              // fuzzy match 
  NONE_MATCHSTATE,                               // no match
  EXACT_MATCHSTATE,                              // exact match 
  EXACTEXACT_MATCHSTATE                          // exact-exact match (match from same document and same segment)      
} EQFMATCHSTATE, *PEQFMATCHSTATE;

// retrieve the match level of a memory proposal
/*! \brief Create a new folder
    \param hSession the session handle returned by the EqfStartSession call
    \param pSegment pointer to the segment info
    \param pProposal pointer to the memory proposal info
    \param psMatchLevel pointer to caller's match level field
    \param psMatchState pointer to caller's match state field
    \param lOptions options to be used by the API call
           - NO_GENERIC_INLINETAG_REPL_OPT suppress inline tag replacement
           - USE_GENERIC_INLINETAG_REPL_OPT perform generic inline tag replacement
    \returns 0 if successful or an error code in case of failures
*/
USHORT EqfGetMatchLevel
(
  HSESSION         hSession,           // non-DDE session handle
  PEQFSEGINFO      pSegment,           // pointer to segment info
  PEQFSEGINFO      pProposal,          // pointer to memory proposal info
  SHORT            *psMatchLevel,      // pointer to caller's match level field
  SHORT            *psMatchState,        // pointer to caller's match state field
  LONG             lOptions            // options to be used by the API call
);

/*! \brief Retrieve the match level of a memory proposal (simplified calling syntax)
    \param hSession the session handle returned by the EqfStartSession call
    \param pszSegmentText segment text (Unicode UTF-16 encoded)
    \param pszProposalText memory proposal text (Unicode UTF-16 encoded)
    \param pszLanguage source language of segment and memory proposal (OpenTM2 language name)
    \param pszSegmentMarkup markup table name of the segment
    \param pszProposalMarkup markup table name of the memory proposal
    \param lOptions options to be used by the API call
           - NO_GENERIC_INLINETAG_REPL_OPT suppress inline tag replacement
           - USE_GENERIC_INLINETAG_REPL_OPT perform generic inline tag replacement
    \returns 0 if successful or an error code in case of failures
*/
SHORT EqfSimpleGetMatchLevel
(
  HSESSION         hSession,           // non-DDE session handle
  WCHAR            *pszSegmentText,    // segment text
  WCHAR            *pszProposalText,   // memory proposal text
  PSZ              pszLanguage,        // source language of segment and memory proposal
  PSZ              pszSegmentMarkup,   // markup table name of segment
  PSZ              pszProposalMarkup,  // markup table name of memory proposal
  LONG             lOptions            // options to be used by the API call

);



// options fpr EqfCleanMatch API call

// create internal memory
#define CLEANMEM_INTERNAL_MEMORY_OPT  0x00000001 

// create external memory
#define CLEANMEM_EXTERNAL_MEMORY_OPT  0x00000002

// return when all activitiy has been completed (instead of iterative processing)
#define CLEANMEM_COMPLETE_IN_ONE_CALL_OPT 0x01000000
#define COMPLETE_IN_ONE_CALL_OPT 0x01000000


// activate logging (will append log info to the log file \EQF\LOGS\CLEANMEMORY.LOG)
#define CLEANMEM_LOGGING_OPT          0x00010000

// if specified only the best match will be written to the output memory
// if not specified the best 3 fuzzy matches will be written to the output memory
#define CLEANMEM_BESTMATCH_OPT        0x00020000

// merge into existing internal memory
#define CLEANMEM_MERGE_OPT            0x20000000

// keep duplicate exact matches and fuzzy matches in the memory
#define CLEANMEM_KEEP_DUPS_OPT       0x40000000

/*! \brief Remove irrelevant (for the given folder) proposals from an external memory
    The relevant segments are either stored in an internal or external memory. The external memory format
    is EXP in UTF-16 encoding.
    \param hSession the session handle returned by the EqfStartSession call
    \param pszFolder name of folder containing the translatable material
    \param pszInMemory fully qualified name of external input memory (EXP format, encoding: UTF-16)
    \param pszOutMemory name of internal output memory or fully qualified name of external output memory
    \param lOptions options for processing
           - CLEANMEM_INTERNAL_MEMORY_OPT write the relevant proposals to an internal memory
           - CLEANMEM_EXTERNAL_MEMORY_OPT write the relevant proposals to an external memory
           - COMPLETE_IN_ONE_CALL_OPT complete the process in one call, without this option the function processes a small unit and
             returns to the calling process with a return code of CONTINUE_RC, the calling process has to re-call the API call until
             any other return code is returned
           - CLEANMEM_LOGGING_OPT activate logging (will append log info to the log file \OTM\LOGS\CLEANMEMORY.LOG)
           - CLEANMEM_BESTMATCH_OPT when specified only the best match will be written to the output memory, without this option
             the best 3 matches will be written to the output memory
           - CLEANMEM_MERGE_OPT merge the relevant proposal into an existing internal memory, without this option the memory is cleared
             before adding the relevant proposals
           - CLEANMEM_KEEP_DUPS_OPT keep duplicate exact matches and fuzzy matches in the memory
		   - OVERWRITE_OPT to overwirte any existing output memory
    \returns 0 if successful, CONTINUE_RC to indicate that the processing is not finished yet, or an error code in case of failures
*/
/*@ADDTOSCRIPTER*/  
USHORT EqfCleanMemory
(
  HSESSION         hSession,           // mand: Eqf session handle
  PSZ              pszFolder,          // mand: name of folder containing the translatable material
  PSZ              pszInMemory,        // mand: fully qualified name of external input memory (encoding: UTF-16)
  PSZ              pszOutMemory,       // mand: name of internal output memory or fully qualified name of external output memory
  LONG             lOptions            // opt: options for processing
                                       // @Output:CLEANMEM_INTERNAL_MEMORY_OPT,CLEANMEM_EXTERNAL_MEMORY_OPT
                                       // @Other: {CLEANMEM_LOGGING_OPT, CLEANMEM_BESTMATCH_OPT, CLEANMEM_MERGE_OPT, CLEANMEM_KEEP_DUPS_OPT,COMPLETE_IN_ONE_CALL_OPT, OVERWRITE_OPT}
);

// rename modes
#define RENAME_FOLDER        1
#define RENAME_MEMORY        2
#define RENAME_DICTIONARY    4

// options
#define ADJUSTREFERENCES_OPT  0x04000000

/*! \brief Rename a folder, Translation Memory, or a dictionary
    \param hSession the session handle returned by the EqfStartSession call
    \param usMode rename mode
           - RENAME_FOLDER to rename a folder
           - RENAME_MEMORY to rename a Translation Memory
           - RENAME_DICTIONARY to rename a dictionary
    \param pszName name of the object being renamed
    \param pszNewName new name of the object
    \param lOptions options for processing
           - ADJUSTREFERENCES_OPT adjust any references to the renamed object
    \returns 0 if successful or an error code in case of failures
*/
/*@ADDTOSCRIPTER*/  
USHORT EqfRename
(
  HSESSION         hSession,           // mand: Eqf session handle
  USHORT           usMode,             // mand: rename mode: 
                                       // @Mode:RENAME_FOLDER, RENAME_MEMORY, RENAME_DICTIONARY
  PSZ              pszName,            // mand: name of object being renamed
  PSZ              pszNewName,         // mand: new name of object
  LONG             lOptions            // opt: options for processing
                                       // @Option:ADJUSTREFERENCES_OPT
);


/*! \brief Process a SNOMATCH file
        Run one or more SNOMATCH (Segments with NO MATCH in the searched Translation Memory databases) files against a Translation Memory and copy all relevant memory proposals
        to the output memory, for the segments contained in the SNOMATCH files a memory match count report and a duplicate word count report is created.
        When the option COMPLETE_IN_ONE_CALL_OPT The processing is performed in small units and the API has to be called repetively until a return code other than CONTINUE_RC uis returned
    \param hSession the session handle returned by the EqfStartSession call
    \param pszNomatch fully qualified name of a single SNOMATCH file, the name of a folder containing SNOMATCH files or a search path (using wild-card characters)
           for a group of SNOMATCH files
    \param pszInMemory name of the internal input memory
    \param pszOutMemory name of internal output memory (is created if it does not exist)
    \param pszMemMatchReportText fully qualified file name of the memory match count report (text format)
    \param pszMemMatchReportXml fully qualified file name of the memory match count report (XML format)
    \param pszDupReportText fully qualified file name of the duplicate word count report (text format)
    \param pszDupReportXml fully qualified file name of the duplicate word count report (XML format)
    \param lOptions options for processing
           - COMPLETE_IN_ONE_CALL_OPT complete the processing in one call to the API
    \returns 0 if successful or an error code in case of failures
*/
/*@ADDTOSCRIPTER*/ 
USHORT EqfProcessNomatch
(
  HSESSION    hSession,                // mand: Eqf session handle
  PSZ         pszNomatch,              // mand: fully qualified name of the SNOMATCh file, folder name or search path
  PSZ         pszInMemory,             // mand: name of the internal input memory
  PSZ         pszOutMemory,            // mand: name of internal output memory (is created if it does not exist)
  PSZ         pszMemMatchReportText,   // opt: fully qualified file name of the memory match count report (text format)
  PSZ         pszMemMatchReportXml,    // opt: fully qualified file name of the memory match count report (XML format)
  PSZ         pszDupReportText,        // opt: fully qualified file name of the duplicate word count report (text format)
  PSZ         pszDupReportXml,         // opt: fully qualified file name of the duplicate word count report (XML format)
  LONG        lOptions                 // opt: options for processing
                                       // @Options: {COMPLETE_IN_ONE_CALL_OPT,RESPECTCRLF_OPT}
);
/*! \brief Process a SNOMATCH file (version with additional parameters)
        Run one or more SNOMATCH (Segments with NO MATCH in the searched Translation Memory databases) files against a Translation Memory and copy all relevant memory proposals
        to the output memory, for the segments contained in the SNOMATCH files a memory match count report and a duplicate word count report is created.
        When the option COMPLETE_IN_ONE_CALL_OPT The processing is performed in small units and the API has to be called repetively until a return code other than CONTINUE_RC uis returned
    \param hSession the session handle returned by the EqfStartSession call
    \param pszNomatch fully qualified name of a single SNOMATCH file, the name of a folder containing SNOMATCH files or a search path (using wild-card characters)
           for a group of SNOMATCH files
    \param pszInMemory name of the internal input memory
    \param pszOutMemory name of internal output memory (is created if it does not exist)
    \param pszMemMatchReportText fully qualified file name of the memory match count report (text format)
    \param pszMemMatchReportXml fully qualified file name of the memory match count report (XML format)
    \param pszDupReportText fully qualified file name of the duplicate word count report (text format)
    \param pszDupReportXml fully qualified file name of the duplicate word count report (XML format)
    \param pszOutNomatchXml fully qualified file name of the output nomatch file in nfluent XML format
    \param pszOutNomatchExp fully qualified file name of the output nomatch file in OpenTM2 EXP format
    \param lOptions options for processing
           - COMPLETE_IN_ONE_CALL_OPT complete the processing in one call to the API
    \returns 0 if successful or an error code in case of failures
*/
/*@ADDTOSCRIPTER*/ 
USHORT EqfProcessNomatchEx
(
  HSESSION    hSession,                // mand: Eqf session handle
  PSZ         pszNomatch,              // mand: fully qualified name of the SNOMATCh file, folder name or search path
  PSZ         pszInMemory,             // mand: name of the internal input memory
  PSZ         pszOutMemory,            // mand: name of internal output memory (is created if it does not exist)
  PSZ         pszMemMatchReportText,   // opt:  fully qualified file name of the memory match count report (text format)
  PSZ         pszMemMatchReportXml,    // opt:  fully qualified file name of the memory match count report (XML format)
  PSZ         pszDupReportText,        // opt:  fully qualified file name of the duplicate word count report (text format)
  PSZ         pszDupReportXml,         // opt:  fully qualified file name of the duplicate word count report (XML format)
  PSZ         pszOutNomatchXml,        // opt:  fully qualified file name of the output nomatch file in nfluent XML format
  PSZ         pszOutNomatchExp,        // opt:  fully qualified file name of the output nomatch file in TM EXP format
  LONG        lOptions                 // opt:  options for processing
                                       // @Options: {COMPLETE_IN_ONE_CALL_OPT,RESPECTCRLF_OPT}
);
/*! \brief Open a document in OpenTM2 at the given location
    \param hSession the session handle returned by the EqfStartSession call
    \param pszFolderName name of the folder
    \param pszDocument name of the document
    \param ulSegNum segment number of the segment to be activated
    \param ulLine line to be activated (ulSegNum has to be 0 to use the line number)
    \returns 0 if successful or an error code in case of failures
*/
/*@ADDTOSCRIPTER*/ 
USHORT EqfOpenDoc
(
  HSESSION    hSession,                // mand: Eqf session handle
  PSZ         pszFolderName,           // mand: name of the folder
  PSZ         pszDocument,             // mand: name of document
  ULONG       ulSegNum,                // opt: segment number of segment to be activated
  ULONG       ulLine                   // opt: line to be activated (ulSegNum has to be 0)
);
/*! \brief Open a document in OpenTM2 at the given location (extented version)
    \param hSession the session handle returned by the EqfStartSession call
    \param pszFolderName name of the folder
    \param pszDocument name of the document
    \param ulSegNum segment number of the segment to be activated
    \param ulLine line to be activated (ulSegNum has to be 0 to use the line number)
    \param pszSearch UTF-16 encode search string (ulSegNum and ulLine have to be 0 to search for a string)
    \returns 0 if successful or an error code in case of failures
*/
/*@ADDTOSCRIPTER*/ 
USHORT EqfOpenDocEx
(
  HSESSION    hSession,                // mand: Eqf session handle
  PSZ         pszFolderName,           // mand: name of the folder
  PSZ         pszDocument,             // mand: name of document
  ULONG       ulSegNum,                // opt:  segment number of segment to be activated
  ULONG       ulLine,                  // opt:  line to be activated (ulSegNum has to be 0)
  wchar_t*    pszSearch                // opt:  UTF-16 search string (ulSegNum and ulLine have to be 0)
);

/*! \brief Open a document in OpenTM2 at the given location
    \param hSession the session handle returned by the EqfStartSession call
    \param pszFolderName name of the folder
    \param pszTrackID TVT tracking ID of the segment to be activated
    \returns 0 if successful or an error code in case of failures
*/
/*@ADDTOSCRIPTER*/ 
USHORT EqfOpenDocByTrack
(
  HSESSION    hSession,                // mand: Eqf session handle
  PSZ         pszFolderName,           // mand: name of the folder
  PSZ         pszTrackID               // mand: TVT tracking ID of segment to be activated
);

/*! \brief Delete the MT log files of a folder
    \param hSession the session handle returned by the EqfStartSession call
    \param pszFolderName name of the folder
    \returns 0 if successful or an error code in case of failures
*/
/*@ADDTOSCRIPTER*/ 
USHORT EqfDeleteMTLog
(
  HSESSION    hSession,                // mand: Eqf session handle
  PSZ         pszFolderName            // mand: name of the folder
);

// constants for API call EqfGetShortName

#define FOLDER_OBJ    1
#define MEMORY_OBJ    2
#define DICT_OBJ      3
#define DOCUMENT_OBJ  4 

// 

/*! \brief Get the internally used short name for a folder, dictionary, Translation Memory, or document
      Attention: this API function will only work for the older OpenTM2 plugins. Newer plugins will (hopefully)
      not use short names anymore
    \param hSession the session handle returned by the EqfStartSession call
    \param ObjectType type of the object being processed
           - FOLDER_OBJ object is a folder
           - MEMORY_OBJ object is a Translation Memory
           - DICT_OBJ object is a dictionary
           - DOCUMENT_OBJ object is a document
    \param pszLongName long name of the object
           for documents also the folder name has to be specified in the form foldername:documentname
    \param pszShortName pointer to a buffer for the returned short name
    \returns 0 if successful or an error code in case of failures
*/
/*@ADDTOSCRIPTER*/ 
USHORT EqfGetShortName
(
  HSESSION    hSession,                // mand: Eqf session handle
  USHORT      ObjectType,              // mand: type of object being processed,
                                       // @Type: FOLDER_OBJ, MEMORY_OBJ, DICT_OBJ, DOCUMENT_OBJ
  PSZ         pszLongName,             // mand: long name of the object, for DOCUMENT_OBJ, 
                                       //       use a colon between folder-name and document-name as "folder-name:document-name"
  PSZ         pszShortName             // mand: buffer for returned short name
);

/*! \brief Remove a group of documents based on a list of document names in a plain text file
    \param hSession the session handle returned by the EqfStartSession call
    \param pszFolderName name of the folder containing the documents
    \param pszListFile fully qualified name of text file containing the list of document names
    \returns 0 if successful or an error code in case of failures
*/
/*@ADDTOSCRIPTER*/ 
USHORT EqfRemoveDocs
(
  HSESSION    hSession,                // mand: Eqf session handle
  PSZ         pszFolderName,           // mand: name of the folder
  PSZ         pszListFile              // mand: name of text file containing the list of document names
);
/*! \brief Restore a group of documents removed using the EqfRemoveDocs API call
    \param hSession the session handle returned by the EqfStartSession call
    \param pszFolderName name of the folder containing the documents
    \returns 0 if successful or an error code in case of failures
*/
/*@ADDTOSCRIPTER*/ 
USHORT EqfRestoreDocs
(
  HSESSION    hSession,                // mand: Eqf session handle
  PSZ         pszFolderName            // mand: name of the folder
);

/*! \brief Associate a HAMSTER/Global memory CTID options file to a folder
    \param hSession the session handle returned by the EqfStartSession call
    \param pszFolderName name of the folder
    \param pszCTIDListFile fully qualified name of the CTID list file
    \returns 0 if successful or an error code in case of failures
*/
 /*@ADDTOSCRIPTER*/ 
USHORT EqfAddCTIDList
(
  HSESSION    hSession,                // mand: Eqf session handle
  PSZ         pszFolderName,           // mand: name of the folder
  PSZ         pszCTIDListFile          // mand: fully qualified name of the CTID list file
);

/*! \brief Export segments contained in specific tag groups
\param hSession the session handle returned by the EqfStartSession call
\param pszFolderName name of the folder
\param pszDocuments list with document names or NULL to process all documents of the folder
\param pszStartStopFile file containing the start/stop tag list
\param pszOutFile fully qualified name of the output file receiving the segment data
\param lOptions options for the processing
       - OVERWRITE_OPT overwrite any existing output file
       - COMPLETE_IN_ONE_CALL_OPT complete processing in one single call to the API
\returns 0 if successful or an error code in case of failures
*/
/*@ADDTOSCRIPTER*/ 
USHORT EqfExportSegs
(
  HSESSION    hSession,                // mand: Eqf session handle
  PSZ         pszFolderName,           // mand: name of folder
  PSZ         pszDocuments,            // opt: list with document names or NULL
  PSZ         pszStartStopFile,        // mand: file containing start/stop tag list
  PSZ         pszOutFile,              // mand: name of output file
  LONG        lOptions                 // opt:  options 
                                       // @Other: {COMPLETE_IN_ONE_CALL_OPT, OVERWRITE_OPT}
);
/*! \brief Check the existence of a folder
    \param hSession the session handle returned by the EqfStartSession call
    \param pszFolderName name of the folder
    \returns 0 when the folder exists or an error code
*/
/*@ADDTOSCRIPTER*/ 
USHORT EqfFolderExists
(
  HSESSION    hSession,                // mand: Eqf session handle
  PSZ         pszFolderName            // mand: name of folder
);

/*! \brief Check the existence of a Translation Memory
    \param hSession the session handle returned by the EqfStartSession call
    \param pszMemoryName name of the Translation Memory
    \returns 0 when the Translation Memory exists or an error code
*/
/*@ADDTOSCRIPTER*/ 
USHORT EqfMemoryExists
(
  HSESSION    hSession,                // mand: Eqf session handle
  PSZ         pszMemoryName            // mand: name of the memory
);

/*! \brief Check the existence of a dictionary
    \param hSession the session handle returned by the EqfStartSession call
    \param pszDictionaryName name of the dictionary
    \returns 0 when the dictionary exists or an error code
*/
/*@ADDTOSCRIPTER*/ 
USHORT EqfDictionaryExists
(
  HSESSION    hSession,                // mand: Eqf session handle
  PSZ         pszDictionaryName        // mand: name of the dictionary
);

/*! \brief Check the existence of a document
    \param hSession the session handle returned by the EqfStartSession call
    \param pszDocumentName name of the document
    \returns 0 when the document exists or an error code
*/
/*@ADDTOSCRIPTER*/ 
USHORT EqfDocumentExists
(
  HSESSION    hSession,                // mand: Eqf session handle
  PSZ         pszFolderName,           // mand: name of folder containing the document
  PSZ         pszDocumentName          // mand: name of the document
);

/**
  \brief Count the number of words in a given string
 
  \param hSession OpenTM2 session handle returned by EqfStartSession
 	\param pszMarkup name of the markup table to be used for the recognition of in-line tags,
   if this parameter is NULL no in-line tag recognition will be performed
 	\param pszLanguage OpenTM2 name for the language of the given text
 	\param pszText null-terminated string containing the text to be counted, the encoding is UTF-16
  \param pulWords points to an unsigned long value receiving the number of words in the text
  \param pulInlineTags points to an unsigned long value receiving the number of inline tags in the text
 	\returns 0 if successful or an error code
 	
**/
/*@ADDTOSCRIPTER*/ 
unsigned short EqfCountWordsInString
(
  HSESSION    hSession,                // mand: Eqf session handle
  char*       pszMarkup,               // opt: name of the markup table to be used for the recognition of in-line tags,if this parameter is NULL no in-line tag recognition will be performed
  char*       pszLanguage,             // mand: OpenTM2 name for the language of the given text
  wchar_t*    pszText,                 // mand: null-terminated string containing the text to be counted, the encoding is UTF-16
  ULONG*      pulWords,                // mand: points to an unsigned long value receiving the number of words in the text
  ULONG*      pulInlineTags            // mand: points to an unsigned long value receiving the number of inline tags in the text
);
/**
 \brief Check the spelling of a list of words

 \param hSession OpenTM2 session handle returned by EqfStartSession
	\param pszLanguage name of the language being used for the spell checking
	\param pszInputTerms a comma separated list of terms or NULL if a input file is being used
	\param pszInputFile the fully qualified name of a plain text file containing the terms, one term per line or NULL if pszInputTerms is being used
  \param pszReport name of the report file receiving the results of the operation
  \param lOption options for the output of the report: TEXT_OUTPUT_OPT for plain text output (CSV) or XML_OUTPUT_OPT (default) for XML output
	\returns 0 if successful or an error code
	
**/
/*@ADDTOSCRIPTER*/ 
unsigned short EqfCheckSpelling
(
  HSESSION    hSession,                // mand: Eqf session handle
  char*       pszLanguage,             // mand: name of the language being used for the spell checking
  char*       pszInputTerms,           // opt:  a comma seperated list of terms or NULL if a input file is being used
  char*       pszInputFile,            // opt:  the fully qualified name of a plain text file containing the terms, one term per line or NULL if pszInputTemrs is being used
  char*       pszReport,               // mand: name of the report file receiving the results of the operation, the report is in the XML format
  LONG        lOptions                 // opt:options 
                                       // @Output Format: TEXT_OUTPUT_OPT,XML_OUTPUT_OPT(default)
);
/**
 \brief Reduce a list of words to their stem form

 \param hSession OpenTM2 session handle returned by EqfStartSession
 \param pszLanguage name of the language being used for the spell checking
 \param pszInputTerms a comma separated list of terms or NULL if a input file is being used
 \param pszInputFile the fully qualified name of a plain text file containing the terms, one term per line or NULL if pszInputTerms is being used
 \param pszReport name of the report file receiving the results of the operation
 \param lOption options for the output of the report
     - TEXT_OUTPUT_OPT for plain text output (CSV) or 
     - XML_OUTPUT_OPT (= default) for XML output
	\returns 0 if successful or an error code
	
**/
/*@ADDTOSCRIPTER*/ 
unsigned short EqfReduceToStemForm
(
  HSESSION    hSession,                // mand: Eqf session handle
  char*       pszLanguage,             // mand: name of the language being used for the stem form reduction
  char*       pszInputTerms,           // mand: a comma seperated list of terms or NULL if a input file is being used
  char*       pszInputFile,            // mand: the fully qualified name of a plain text file containing the terms, one term per line or NULL if pszInputTemrs is being used
  char*       pszReport,               // mand: name of the report file receiving the results of the operation, the report is in the XML format
  LONG        lOptions                 // opt: options 
                                       // @Output Format:TEXT_OUTPUT_OPT,XML_OUTPUT_OPT(default)
);
/*! \brief Clears the MT flag of an external memory in the EXP format
  
  This API function processes a memory in the .EXP format (encoding UTF-16, ANSI. or ASCII) and
  clears any machine translation flag (MT flags) of the memory proposals.
  When an output memory is specified the processed memory is written to the specified output file
  otherwise the input memory is overwritten with the modified memory.

  \param pszInMemory fully qualified file name of the input memory
  \param pszOutMemory fully qualified file name of the output memory, if not specified the output memory overwrites the input memory
	\returns 0 if successful or an error code in case of failures
*/
/*@ADDTOSCRIPTER*/ 
unsigned short EqfClearMTFlag
(
  HSESSION    hSession,                // mand: Eqf session handle
  char*       pszInMemory,             // mand: fully qualified file name of the input memory (the file is in EXP format)
  char*       pszOutMemory             // opt:  fully qualified file name of the output memory, if not specified the input memory is changed directly
);

/*! \brief Checks matches from a NOMATCH file against a memory and applies any Global Memory option file.
  
  This API function looks up all matches contained in a NOMATCH file (in XML format)
  in the given memory and applies the specified Global Memory option file on the memory proposals.
  The function creates a memory match word count and writes any matches not found in the input
  memory to a new NOMATCH file. The new NOMATCH file can be in the XML format and/or the .EXP format.
  The processing is done in small units and the API call is to be called repetitively as long as 
  the return code CONTINUE_RC is returned. To do the processing in one block specify the option
  COMPLETE_IN_ONE_CALL_OPT. The word count report can be created in the XML format (use the option XML_OUTPUT_OPT
  ) or in plain text format (use the option TEXT_OUTPUT_OPT). The word count report creation in plain text format is the default. 

  \param hSession the session handle returned by the EqfStartSession call
  \param pszInNoMatchXML fully qualified file name of the input NOMATCH file in XML format
  \param pszGlobMemOptionFile fully qualified file name of the Global Memory option file
  \param pszMemory Name of the internal memory being used for the look-up. 
  \param pszOutNoMatchXML fully qualified file name of the new NOMATCH file in the XML format (can be NULL when not used)
  \param pszOutNoMatchEXP fully qualified file name of the new NOMATCH file in the EXP format (can be NULL when not used)
  \param pszWordCountReport fully qualified file name of the created memory match word count report (can be NULL when not used)
  \param lOptions options for the processing
    - COMPLETE_IN_ONE_CALL_OPT to do the processing in one call (rather than doing the processing in small units)
    - TEXT_OUTPUT_OPT to create the word count report in plain text format (=default)
    - XML_OUTPUT_OPT to create the word count report in XML format
	\returns 0 if successful or an error code in case of failures
*/
/*@ADDTOSCRIPTER*/ 
unsigned short EqfFilterNoMatchFile
(
  HSESSION    hSession,               // mand: Eqf session handle   
  char*       pszInNoMatchXML,        // mand: fully qualified file name of the input NOMATCH file in XML format   
  char*       pszGlobMemOptionFile,   // mand: fully qualified file name of the Global Memory option file  
  char*       pszMemory,              // mand: Name of the internal memory being used for the lookup.    
  char*       pszOutNoMatchXML,       // opt:  fully qualified file name of the new NOMATCH file in the XML format
  char*       pszOutNoMatchEXP,       // opt:  fully qualified file name of the new NOMATCH file in the EXP format 
  char*       pszWordCountReport,     // opt:  fully qualified file name of the created memory match word count report
  long        lOptions                // opt:  options for the processing
                                      // @Output Format: XML_OUTPUT_OPT,TEXT_OUTPUT_OPT(default) 
                                      // @Other: COMPLETE_IN_ONE_CALL_OPT								  
);

/*! \brief Deletes the given dictionary.
  \param hSession the session handle returned by the EqfStartSession call
  \param pszDict name of the dictionary being deleted
	\returns 0 if successful or an error code in case of failures
*/
/*@ADDTOSCRIPTER*/ 
USHORT EqfDeleteDict
(
  HSESSION    hSession,                // mand: Eqf session handle
  PSZ         pszDictName              // mand: name of dictionary
);

/*! \brief Get OpenTM2 version information
    \param  pszVersion pointer to a buffer for the version string
    \param  length size of the buffer for the version string
    \returns version information
*/
/*@ADDTOSCRIPTER*/
USHORT EqfGetVersionEx
(
  PSZ  pszVersion,                    // mand: to retrieve version information
  int  length                         // /*@Ignore*/ mand: legnth of the retrive buffer  
);

/*! \brief Create match segment IDs for the entries of an internal memory
  \param hSession the session handle returned by the EqfStartSession call
  \param pszMemName name of the Translation Memory
  \param pszTM_ID translation memory ID or NULL if not used
  \param pszStoreID ID for the origin of the translation memory or NULL if not used
  \param lOptions options for adding of match segment IDs
         - FORCENEWMATCHID_OPT create a new match segment ID even if the match already has one
  \returns 0 if successful or an error code in case of failures
*/
/*@ADDTOSCRIPTER*/
USHORT EqfAddMatchSegID
(
  HSESSION    hSession,                // mand: Eqf session handle
  PSZ         pszMemName,              // mand: name of Translation Memory
  PSZ         pszTM_ID,                // opt: translation memory ID or NULL if not used
  PSZ         pszStoreID,              // opt: ID for the origin of the translation memory or NULL if not used
  LONG        lOptions                 // opt: options for the add natch segment ID processing
									                     // @Other: {FORCENEWMATCHID_OPT}
);

/*! \brief Search segments having fuzzy memory proposals
  \param hSession the session handle returned by the EqfStartSession call
  \param pszFolderName name of the folder containing the searched documents
  \param pszDocuments list of documents being searched or NULL to search all documents of the folder
  \param pszOutputFile fully qualified of the file receiving the list of segments having fuzzy proposals
  \param iSearchMode search mode, one of the values UPTOSELECTEDCLASS_MODE, SELECTEDCLASSANDHIGHER_MODE, and ONLYSELECTEDCLASS_MODE
  \param iClass search class, a value from 0 to 6
  \param lOptions options for searching fuzzy segments
         - OVERWRITE_OPT overwrite any existing output file
         - MARKDIFFERENCES_OPT mark the differences between segment source and fuzzy proposal in teh output
  \returns 0 if successful or an error code in case of failures
*/
/*@ADDTOSCRIPTER*/
USHORT EqfSearchFuzzySegments
(
  HSESSION    hSession,                // mand: Eqf session handle
  PSZ         pszFolderName,           // mand: name of folder
  PSZ         pszDocuments,            // opt: list of documents or NULL 
  PSZ         pszOutputFile,           // mand: fully qualified name of output file
  int         iSearchMode,             // mand: search mode
                                       // @Modes: UPTOSELECTEDCLASS_MODE,SELECTEDCLASSANDHIGHER_MODE(default),ONLYSELECTEDCLASS_MODE
  int         iClass,                  // mand: searched class
                                       // @Classes: 0(default),1,2,3,4,5,6
  LONG        lOptions                 // opt: processing options
									                     // @Other: {OVERWRITE_OPT,MARKDIFFERENCES_OPT}
);

/*! \brief Export a memory to a ZIP package
  \param hSession the session handle returned by the EqfStartSession call
  \param pszMemory name of the memory being exported
  \param pszMemoryPackage name of a new ZIP archive receiving the memory files
  \returns 0 if successful or an error code in case of failures
*/
USHORT EqfExportMemInInternalFormat
(
  HSESSION    hSession, 
  PSZ         pszMemoryName,
  PSZ         pszMemoryPackage,
  LONG        lOptions 
);

/*! \brief Open the specified translation memory
  \param hSession the session handle returned by the EqfStartSession call
  \param pszMemory name of the memory being opened
  \param plHandle buffer to a long value receiving the handle of the opened memory or -1 in case of failures
  \param lOptions processing options 
  \returns 0 if successful or an error code in case of failures
*/
USHORT EqfOpenMem
(
  HSESSION    hSession,
  PSZ         pszMemoryName, 
  LONG        *plHandle,
  LONG        lOptions 
);

/*! \brief Close the translation memory referred by the handle
  \param hSession the session handle returned by the EqfStartSession call
  \param lHandle handle of a previously opened memory
  \param lOptions processing options 
  \returns 0 if successful or an error code in case of failures
*/
USHORT EqfCloseMem
(
  HSESSION    hSession, 
  LONG        lHandle,
  LONG        lOptions 
);

/*! \brief Lookup a segment in the memory
  \param hSession the session handle returned by the EqfStartSession call
  \param lHandle handle of a previously opened memory
  \param pSearchKey pointer to a MemProposal structure containing the searched criteria
  \param *piNumOfProposals pointer to the number of requested memory proposals, will be changed on return to the number of proposals found
  \param pProposals pointer to a array of MemProposal structures receiving the search results
  \param lOptions processing options 
  \returns 0 if successful or an error code in case of failures
*/
USHORT EqfQueryMem
(
  HSESSION    hSession,    
  LONG        lHandle,          
  PMEMPROPOSAL pSearchKey, 
  int         *piNumOfProposals,
  PMEMPROPOSAL pProposals, 
  LONG        lOptions     
);

/*! \brief Search the given text string in the memory
  \param hSession the session handle returned by the EqfStartSession call
  \param lHandle handle of a previously opened memory
  \param pszSearchString pointer to the search string (in UTF-16 encoding)
  \param pszStartPosition pointer to a buffer (min size = 20 charachters) containing the start position, on completion this buffer is filled with the next search position
  \param pProposal pointer to an MemProposal structure receiving the next matching segment
  \param lSearchTime max time in milliseconds to search for a matching proposal, 0 for no search time restriction
  \param lOptions processing options
     SEARCH_IN_SOURCE_OPT  search in source
     SEARCH_IN_TARGET_OPT  search in target
  \returns 0 if successful or an error code in case of failures
*/
USHORT EqfSearchMem
(
  HSESSION    hSession,                
  LONG        lHandle,                 
  CHAR_W      *pszSearchString,
  const char* pszSrcLang, 
  const char* pszTrgLang,
  PSZ         pszStartPosition,
  PMEMPROPOSAL pProposal,
  LONG        lSearchTime,
  LONG        lOptions
);

/*! \brief Update a segment in the memory
  \param hSession the session handle returned by the EqfStartSession call
  \param lHandle handle of a previously opened memory
  \param pNewProposal pointer to an MemProposal structure containing the segment data
  \param lOptions processing options 
  \returns 0 if successful or an error code in case of failures
*/
USHORT EqfUpdateMem
(
  HSESSION    hSession,
  LONG        lHandle, 
  PMEMPROPOSAL pNewProposal,
  LONG        lOptions
);


/*! \brief List the name of all memories
\param hSession the session handle returned by the EqfStartSession call
\param pszBuffer pointer to a buffer reiceiving the comma separated list of memory names or NULL to get the required length for the list
\param plLength pointer to a variable containing the size of the buffer area, on return the length of name list is stored in this variable
\returns 0 if successful or an error code in case of failures
*/
USHORT EqfListMem
(
  HSESSION    hSession,
  PSZ         pszBuffer,
  PLONG       plLength
);

/*! \brief Get the OpenTM2 language name for a ISO language identifier
\param hSession the session handle returned by the EqfStartSession call
\param pszISOLang pointer to ISO language name (e.g. en-US )
\param pszOpenTM2Lang buffer for the OpenTM2 language name
\returns 0 if successful or an error code in case of failures
*/
USHORT EqfGetOpenTM2Lang
(
  HSESSION    hSession,
  PSZ         pszISOLang,
  PSZ         pszOpenTM2Lang, 
  bool*       pfPrefered = nullptr
);

std::vector<std::string> GetListOfLanguagesFromFamily(PSZ pszIsoLang);

/*! \brief Get the ISO language identifier for a OpenTM2 language name
\param hSession the session handle returned by the EqfStartSession call
\param pszOpenTM2Lang pointer to the OpenTM2 language name
\param pszISOLang pointer to a buffer for the ISO language identifier
\returns 0 if successful or an error code in case of failures
*/
USHORT EqfGetIsoLang
(
  HSESSION    hSession,
  PSZ         pszOpenTM2Lang,
  PSZ         pszISOLang
);


/*! \brief Connet to LAN based shared memory
\param hSession the session handle returned by the EqfStartSession call
\param chDrive the drive where to look for the memory
\param pszMemName the memory name
\returns 0 if successful or an error code in case of failures
*/
USHORT EqfConnectSharedMem
(
  HSESSION    hSession,
  CHAR        chDrive,
  PSZ         pszMemName
);

/*! \brief Disconnet to LAN based shared memory
\param hSession the session handle returned by the EqfStartSession call
\param chDrive the drive where to look for the memory
\param pszMemName the memory name
\returns 0 if successful or an error code in case of failures
*/
USHORT EqfDisconnectSharedMem
(
  HSESSION    hSession,
  CHAR        chDrive,
  PSZ         pszMemName
);


#endif


///end of OTMFUNC region

#endif //_tm_h_included_