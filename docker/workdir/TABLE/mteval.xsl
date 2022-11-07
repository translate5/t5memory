﻿<!--
    Copyright (c) 1999-2016, International Business Machines
    Corporation and others.  All rights reserved.
-->

<!-- &nbsp; does not exists in XPath, so defined as the real unicode character 160
     which is the non breaking space character and provides exactly the same result than using &nbsp; -->
     
<!DOCTYPE xsl:stylesheet 
	[
		<!ENTITY nbsp "&#160;">
	]>

<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:fo="http://www.w3.org/1999/XSL/Format"  xmlns:PE="http://www.ibm.com/PostEdit" >
    <xsl:variable name="base" select="'words'" />

<!-- =========================================================================================== --> 	
<!-- == Date of Stylesheet (original): January 01, 2005                                       == -->
<!-- == Created by                   : Gerhard Queck                                          == -->
<!-- == Date of Stylesheet (update)  : March 2, 2016                                     == -->
<!-- == Updated by                   : Gerhard Queck                                           == -->
<!-- == Purpose                      : Display the content of a MT log in a browser           == -->
<!-- == Version                      : 3.6                                                    == -->
<!-- =========================================================================================== -->
	
<!-- =========================================================================================== --> 	
<!-- ========================== The XSL Template Control Element =============================== -->
<!-- =========================================================================================== -->
<xsl:template match="/">
   <html>
     <!-- <head> required to put <META http-equiv="Content-Type" content="text/html; charset=utf-8">
     generated by output encoding attribute -->
      <head></head>
      <body>
         <xsl:call-template name="reportheader" />          <!-- Generate the Report Header      -->
		 <xsl:call-template name="folderlist">              <!-- Generate the the Folder List    -->
		    <xsl:with-param name="base" select="$base" />
		 </xsl:call-template>
		 <xsl:call-template name="summary">                 <!-- Generate the Summary            -->
		    <xsl:with-param name="base" select="$base" />
		 </xsl:call-template>
      </body>
   </html>
</xsl:template>
<!-- =========================================================================================== -->


<!-- =========================================================================================== --> 	
<!-- ========================== The Report Header ============================================== -->
<!-- =========================================================================================== -->	
<xsl:template name = "reportheader" >
	<P><BR/></P>
	<TABLE border="1">
	   <TBODY>
		  <TR>
			 <TD width="380" bgcolor="#d3d3d3" align="right">MT Evaluation:&nbsp;</TD>
			 <TD width="300" bgcolor="#f7f7f7">&nbsp;</TD>
		  </TR>
		  <TR>
			 <TD bgcolor="#d3d3d3" align="right">Version of MTEVAL:&nbsp;</TD>
			 <TD bgcolor="#f7f7f7"><xsl:value-of select="/mtevaluation/header/generatorversion"/></TD>
		  </TR>
		  <TR>
			 <TD bgcolor="#d3d3d3" align="right">Report Generation Date:&nbsp;</TD>
			 <TD bgcolor="#f7f7f7"><xsl:value-of select="/mtevaluation/header/creationdate"/></TD>
		  </TR>
		  <TR>
			 <TD bgcolor="#d3d3d3" align="right">Input specification:&nbsp;</TD>
			 <TD bgcolor="#f7f7f7"><xsl:value-of select="/mtevaluation/header/inputspecs"/></TD>
		  </TR>
	   </TBODY>
	</TABLE>
</xsl:template>
<!-- =========================================================================================== -->	


<!-- =========================================================================================== --> 	
<!-- ========================== Create Folder List ============================================= -->
<!-- =========================================================================================== -->
<xsl:template  name="folderlist" >
	<xsl:param name="base"></xsl:param>
	<P><BR/></P>
	<TABLE border="1">
	   <TBODY>
		  <TR>
			 <TD width="380" bgcolor="#d3d3d3" align="right">MT Evaluation:&nbsp;</TD>
			 <TD width="300" bgcolor="#f7f7f7" align="left">Folder list</TD>
		  </TR>
	   </TBODY>
	</TABLE>
	<xsl:for-each select="/mtevaluation/folder"> 
			<xsl:call-template  name="showfolder">
				<xsl:with-param name="folder" select="." />
				<xsl:with-param name="base" select="$base" />
			</xsl:call-template>
	</xsl:for-each>
</xsl:template>
<!-- =========================================================================================== -->


<!-- =========================================================================================== --> 	
<!-- ========================== Display Single FOLDER ========================================== -->
<!-- =========================================================================================== -->
<xsl:template  name="showfolder" >
	<xsl:param name="folder"></xsl:param>
	<xsl:param name="base"></xsl:param>
	<TABLE border="1">
	   <TBODY>
		  <TR>
			 <TD width="380" bgcolor="#d3d3d3" align="right">Folder:&nbsp;</TD>
			 <TD width="300" bgcolor="#f7f7f7" align="left"><xsl:value-of select="$folder/@name"/></TD>
		  </TR>
		  <TR>
			 <TD bgcolor="#d3d3d3" align="right">Option "Send to MT server" used:&nbsp;</TD>
			 <TD bgcolor="#f7f7f7">
				<xsl:if test="$folder/@MTInfoAvailable=1">Yes</xsl:if>
				<xsl:if test="$folder/@MTInfoAvailable=0">No</xsl:if>
			</TD>
		  </TR>
		  <TR>
			 <TD bgcolor="#d3d3d3" align="right">MT job received:&nbsp;</TD>
			 <TD bgcolor="#f7f7f7">
				<xsl:if test="$folder/@MTJobReceived=1">Yes</xsl:if>
				<xsl:if test="$folder/@MTJobReceived=0">No</xsl:if>
			  </TD>
		  </TR>
	   </TBODY>
	</TABLE>
		  
		  <xsl:variable name="rowspan1" select="count($folder/mtJobData/counts[@base=$base])"/>
		  <xsl:variable name="mtinfo"   select="$folder/@MTInfoAvailable" />
		  <xsl:if test="$mtinfo = 1" >
			<TABLE border="1">
			   <TBODY>
				  <TR>
					 <TD width="280" valign="top" bgcolor="#d3d3d3" align="center">&nbsp;</TD>
					 <TD width="180" valign="top" bgcolor="#d3d3d3" align="center">Type</TD>
					 <TD width="60"  valign="top" bgcolor="#d3d3d3">simple<BR/>1..4<BR/>words</TD>
					 <TD width="60"  valign="top" bgcolor="#d3d3d3">medium<BR/>5..14<BR/>words</TD>
					 <TD width="60"  valign="top" bgcolor="#d3d3d3" align="center">complex<BR/>15++<BR/>words</TD>
					 <TD width="60"  valign="top" bgcolor="#d3d3d3" align="center">Total</TD>
				  </TR>
					<xsl:for-each select="$folder/mtJobData/counts[@base=$base]"> 
						<tr align="left" bgcolor="white">
						   <xsl:if test="position()=1">
								<td rowspan="{$rowspan1}">MT Job data</td>
						   </xsl:if>
							<xsl:call-template  name="showcounts">
								<xsl:with-param name="counts" select="." />
								<xsl:with-param name="type" ><xsl:value-of select="@type"/></xsl:with-param>
							</xsl:call-template>
						</tr>
					</xsl:for-each>
			   </TBODY>
			</TABLE>
	    </xsl:if>
	<P><BR/></P>
		 <xsl:for-each select="$folder/document"> 
	<TABLE border="1">
	   <TBODY>
		    <TR>
		    <TD  valign="top" bgcolor="#d3d3d3" align="center" colspan="19" >Document <xsl:value-of select="./@name"/></TD>
		  </TR>
		  <TR>
			 <TD width="80"  valign="top" bgcolor="#d3d3d3" align="center">Segment ID</TD>
			 <TD width="60"  valign="top" bgcolor="#d3d3d3" align="center">Words</TD>
			 <TD width="60"  valign="top" bgcolor="#d3d3d3" align="center">Process Time (Sec)</TD>
			 <TD width="60"  valign="top" bgcolor="#d3d3d3" align="center">Choice Time (Sec)</TD>
			 <TD width="60"  valign="top" bgcolor="#d3d3d3" align="center">Think Time (Sec)</TD>
			 <TD width="60"  valign="top" bgcolor="#d3d3d3" align="center">Edit Time (Sec)</TD>
			 <TD width="60"  valign="top" bgcolor="#d3d3d3" align="center">Total Time (Sec)</TD>
			 <TD width="60"  valign="top" bgcolor="#d3d3d3" align="center">Chars Typed</TD>
			 <TD width="120"  valign="top" bgcolor="#d3d3d3" align="center">Existing Proposal</TD>
			 <TD width="120"  valign="top" bgcolor="#d3d3d3" align="center">Used Proposal</TD>
			 <TD width="60"  valign="top" bgcolor="#d3d3d3" align="center">AutoSubst</TD>
			 <TD width="200"  valign="top" bgcolor="#d3d3d3" align="center">Time Stamp</TD>
			 <TD width="460"  valign="top" bgcolor="#d3d3d3" align="center">Segment source</TD>
			 <TD width="200"  valign="top" bgcolor="#d3d3d3" align="center">MT metadata</TD>
			 <TD width="460"  valign="top" bgcolor="#d3d3d3" align="center">Segment target</TD>
			 <TD width="100"  valign="top" bgcolor="#d3d3d3" align="center">Used match ID</TD>
			 <TD width="460"  valign="top" bgcolor="#d3d3d3" align="center">Used match target</TD>
			 <TD width="100"  valign="top" bgcolor="#d3d3d3" align="center">MT match ID</TD>
			 <TD width="460"  valign="top" bgcolor="#d3d3d3" align="center">MT match target</TD>
		  </TR>
      <xsl:call-template name="showdocumentdetail">
		      <xsl:with-param name="document" select="." />
			  <xsl:with-param name="base" select="$base" />
		   </xsl:call-template>
	   </TBODY>
	</TABLE>
	<P><BR/></P>
		</xsl:for-each>
	<TABLE border="1">
	   <TBODY>
		  <TR>
			 <TD width="380" valign="top" bgcolor="#d3d3d3" align="center">Document Name</TD>
			 <TD width="180" valign="top" bgcolor="#d3d3d3" align="center">Type</TD>
			 <TD width="60"  valign="top" bgcolor="#d3d3d3" align="center">Simple<BR/>1..4<BR/>words</TD>
			 <TD width="60"  valign="top" bgcolor="#d3d3d3" align="center">Medium<BR/>5..14<BR/>words</TD>
			 <TD width="60"  valign="top" bgcolor="#d3d3d3" align="center">Complex<BR/>15++<BR/>words</TD>
			 <TD width="60"  valign="top" bgcolor="#d3d3d3" align="center">Total</TD>
		  </TR>

		<xsl:variable name="rowspan2"  select="count($folder/foldertotal/counts[@base=$base])"/>
		<xsl:for-each select="$folder/foldertotal/counts[@base=$base]"> 
			<tr align="left" bgcolor="white">
			   <xsl:if test="position()=1">
					<td rowspan="{$rowspan2}">Folder summary</td>
			   </xsl:if>
				<xsl:call-template  name="showcounts">
					<xsl:with-param name="counts" select="." />
					<xsl:with-param name="type" ><xsl:value-of select="@type"/></xsl:with-param>
				</xsl:call-template>
			</tr>
		</xsl:for-each>
	   </TBODY>
	</TABLE>
	<P><BR/></P>
</xsl:template>


<!-- =========================================================================================== --> 	
<!-- ========================== Display a Single Document's Segment DETAILs ==================== -->
<!-- =========================================================================================== -->
<xsl:template name="showdocumentdetail" >
   <xsl:param name="document"></xsl:param>
   <xsl:param name="base"></xsl:param>
   <xsl:variable name="rowspan" select="count($document/counts[@base=$base])"/>
   <xsl:for-each select="$document/segmentList"> 
      <tr align="left" bgcolor="white">
       <td align="left" colspan="19">Shipment <xsl:value-of select="./@shipment" /></td>
      </tr>
  	  	<xsl:for-each select="./segment"> 
      <tr>
  		 <xsl:call-template name="showsegments">
  		    <xsl:with-param name="segment" select="." />
  		 </xsl:call-template>
      </tr>
   </xsl:for-each>
</xsl:for-each>
</xsl:template>
<!-- =========================================================================================== --> 	


<!-- =========================================================================================== --> 	
<!-- ========================== Display a Single DOCUMENT ====================================== -->
<!-- =========================================================================================== -->
<xsl:template  name="showdocument" >
	<xsl:param name="document"></xsl:param>
	<xsl:param name="base"></xsl:param>
	<xsl:variable name="rowspan" select="count($document/counts[@base=$base])"/>
	<xsl:for-each select="$document/counts[@base=$base]"> 
		<tr align="left" bgcolor="white">
		   <xsl:if test="position()=1">
			   <xsl:variable name="docname"><xsl:value-of select="$document/@name"/></xsl:variable>
			   <xsl:variable name="namelen"><xsl:value-of select="string-length($docname)"/></xsl:variable>
			   <xsl:if test="$namelen&lt;=43">
                   <td rowspan="{$rowspan}"><xsl:value-of select="$docname"/>&nbsp;</td>
			   </xsl:if>
			   <xsl:if test="$namelen&gt;43">
                  <td rowspan="{$rowspan}">
				     <xsl:variable name="restpos"><xsl:value-of select="number($namelen)-20"/></xsl:variable>
					 <xsl:value-of select="substring($docname, 1, 20)"/>...<xsl:value-of select="substring($docname,$restpos)"/>
                  </td>
			   </xsl:if>
		   </xsl:if>
			<xsl:call-template  name="showcounts">
				<xsl:with-param name="counts" select="." />
				<xsl:with-param name="type" ><xsl:value-of select="@type"/></xsl:with-param>
			</xsl:call-template>
		</tr>
	</xsl:for-each>
</xsl:template>
<!-- =========================================================================================== -->


<!-- =========================================================================================== --> 	
<!-- ========================== Create Summary ================================================= -->
<!-- =========================================================================================== -->
<xsl:template  name="summary" >
	<xsl:param name="base"></xsl:param>
	<P><BR/></P>
	<TABLE border="1">
	   <TBODY>
		  <TR>
			 <TD width="250" bgcolor="#d3d3d3">MT Evaluation: </TD>
			 <TD width="300" bgcolor="#f7f7f7">Summary</TD>
		  </TR>
		  <TR>
			 <TD bgcolor="#d3d3d3">Folders processed:</TD>
			 <TD bgcolor="#f7f7f7"><xsl:value-of select="/mtevaluation/summary/@folders"/></TD>
		  </TR>
		  <TR>
			 <TD bgcolor="#d3d3d3">Units:</TD>
			 <TD bgcolor="#f7f7f7"><xsl:value-of select="$base"/></TD>
		  </TR>
	   </TBODY>
	</TABLE>

	<TABLE border="1" cellspacing="3">
	   <TBODY>
		  <TR>
			 <TD width="30%" valign="top" bgcolor="#d3d3d3" align="center">Type</TD>
			 <TD width="10%" valign="top" bgcolor="#d3d3d3" align="center">simple<BR/>1..4<BR/>words</TD>
			 <TD width="10%" valign="top" bgcolor="#d3d3d3" align="center">medium<BR/>5..14<BR/>words</TD>
			 <TD width="10%" valign="top" bgcolor="#d3d3d3" align="center">complex<BR/>15++<BR/>words</TD>
			 <TD width="10%" valign="top" bgcolor="#d3d3d3" align="center">Total</TD>
		  </TR>
 			<xsl:for-each select="/mtevaluation/summary/counts[@base=$base]"> 
			   <tr align="left" bgcolor="white">
			      <xsl:call-template  name="showcounts">
				     <xsl:with-param name="counts" select="." />
					 <xsl:with-param name="type" ><xsl:value-of select="@type"/></xsl:with-param>
				  </xsl:call-template>
			   </tr>
			</xsl:for-each>
	   </TBODY>
	</TABLE>
</xsl:template>
<!-- =========================================================================================== -->


<!-- =========================================================================================== --> 	
<!-- ========================== Display the counts of a single category ======================== -->
<!-- =========================================================================================== -->
<xsl:template name="showcounts" >
   <xsl:param name="counts"></xsl:param>
   <xsl:param name="type"></xsl:param>
      <td>
         <xsl:choose>
		    <xsl:when test="$type = 'total'">Processed for MT</xsl:when>
		    <xsl:when test="$type = 'send'">Send to MT server</xsl:when>
		    <xsl:when test="$type = 'received'">Received from MT server</xsl:when>
		    <xsl:when test="$type = 'mtExist'">Existing MT proposals</xsl:when>
		    <xsl:when test="$type = 'mtUsed'">Used MT proposals</xsl:when>
		    <xsl:otherwise><xsl:value-of select="$type"/></xsl:otherwise>
		 </xsl:choose>
      </td>		
	  <td align="right"><xsl:value-of select="$counts/@simple" />&nbsp;</td>
	  <td align="right"><xsl:value-of select="$counts/@medium" />&nbsp;</td>
	  <td align="right"><xsl:value-of select="$counts/@complex" />&nbsp;</td>
	  <td align="right"><xsl:value-of select="$counts/@sum" />&nbsp;</td>
</xsl:template>
<!-- =========================================================================================== --> 	


<!-- =========================================================================================== --> 	
<!-- ========================== Display the counts of a single category ======================== -->
<!-- =========================================================================================== -->
<xsl:template name="showsegments" >
   <xsl:param name="segment"></xsl:param>
    <td align="right"><xsl:value-of select="$segment/@num" />&nbsp;</td>
	  <td align="right"><xsl:value-of select="$segment/@words" />&nbsp;</td>
	  <td align="right"><xsl:value-of select="$segment/@processTime" />&nbsp;</td>
	  <td align="right"><xsl:value-of select="$segment/@choiceTime" />&nbsp;</td>
	  <td align="right"><xsl:value-of select="$segment/@thinkTime" />&nbsp;</td>
	  <td align="right"><xsl:value-of select="$segment/@editTime" />&nbsp;</td>
	  <td align="right"><xsl:value-of select="$segment/@totalTime" />&nbsp;</td>
	  <td align="right"><xsl:value-of select="$segment/@charsTyped" />&nbsp;</td>
	  <td align="left"><xsl:value-of select="$segment/@existingProposal" />&nbsp;</td>
	  <td align="left"><xsl:value-of select="$segment/@usedProposal" />&nbsp;</td>
	  <td align="center"><xsl:value-of select="$segment/@autoSubst" />&nbsp;</td>
	  <td align="center"><xsl:value-of select="$segment/@timestamp" />&nbsp;</td>
	  <td align="left"><xsl:value-of select="$segment/source" />&nbsp;</td>
	  <td align="left">
	     <xsl:call-template name="showmtdata">
 		    <xsl:with-param name="valname" ><xsl:text>TM-MatchType</xsl:text></xsl:with-param>
		    <xsl:with-param name="value"><xsl:value-of select="$segment/metadata/MT/@TM-MatchType" /></xsl:with-param>
         </xsl:call-template>
	     <xsl:call-template name="showmtdata">
 		    <xsl:with-param name="valname" ><xsl:text>MT-ServiceID</xsl:text></xsl:with-param>
		    <xsl:with-param name="value"><xsl:value-of select="$segment/metadata/MT/@MT-ServiceID" /></xsl:with-param>
         </xsl:call-template>
	     <xsl:call-template name="showmtdata">
 		    <xsl:with-param name="valname" ><xsl:text>MT-MetricName</xsl:text></xsl:with-param>
		    <xsl:with-param name="value"><xsl:value-of select="$segment/metadata/MT/@MT-MetricName" /></xsl:with-param>
         </xsl:call-template>
	     <xsl:call-template name="showmtdata">
 		    <xsl:with-param name="valname" ><xsl:text>MT-MetricValue</xsl:text></xsl:with-param>
		    <xsl:with-param name="value"><xsl:value-of select="$segment/metadata/MT/@MT-MetricValue" /></xsl:with-param>
         </xsl:call-template>
	     <xsl:call-template name="showmtdata">
 		    <xsl:with-param name="valname" ><xsl:text>PE-EditDistanceChars</xsl:text></xsl:with-param>
		    <xsl:with-param name="value"><xsl:value-of select="$segment/metadata/MT/@PE-EditDistanceChars" /></xsl:with-param>
         </xsl:call-template>
	     <xsl:call-template name="showmtdata">
 		    <xsl:with-param name="valname" ><xsl:text>PE-EditDistanceWords</xsl:text></xsl:with-param>
		    <xsl:with-param name="value"><xsl:value-of select="$segment/metadata/MT/@PE-EditDistanceWords" /></xsl:with-param>
         </xsl:call-template>
	     <xsl:call-template name="showmtdata">
 		    <xsl:with-param name="valname" ><xsl:text>MT-Fields</xsl:text></xsl:with-param>
		    <xsl:with-param name="value"><xsl:value-of select="$segment/metadata/MT/@MT-Fields" /></xsl:with-param>
         </xsl:call-template>
    &nbsp;</td>
    <td align="left"><xsl:value-of select="$segment/metadata/PE:tgt" />&nbsp;</td>
    <td align="left"><xsl:value-of select="$segment/metadata/PE:usedmatch/@PE:ID_usedmatch" />&nbsp;</td>
    <td align="left"><xsl:value-of select="$segment/metadata/PE:usedmatch" />&nbsp;</td>
    <td align="left"><xsl:value-of select="$segment/metadata/PE:mtmatch/@PE:ID_mtmatch" />&nbsp;</td>
    <td align="left"><xsl:value-of select="$segment/metadata/PE:mtmatch" />&nbsp;</td>
</xsl:template>

<!-- =========================================================================================== --> 	
<!-- ========================== conditionally display MT metadata ===================================== -->
<!-- =========================================================================================== -->
<xsl:template  name="showmtdata" >
	<xsl:param name="valname"></xsl:param>
	<xsl:param name="value"></xsl:param>
       <xsl:if test="$value!=''">
          <xsl:value-of select="$valname" /><xsl:text>=</xsl:text><xsl:value-of select="$value" /><xsl:text> </xsl:text>
       </xsl:if>
</xsl:template>

</xsl:stylesheet>
