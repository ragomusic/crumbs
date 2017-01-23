# Crumbs Document Viewer

![Cookie logo of crumbs](/docs/images/crumbs_logo.png "Crumbs Document Viewer")

## Info
* Created by: Ricardo Garcia (rago) [@ragomusic](https://twitter.com/ragomusic)
* Contact: info .at. crumbssoftware . com
* Github: [https://github.com/ragomusic/crumbs](https://github.com/ragomusic/crumbs)
* Website: [http://crumbssoftware.com](http://crumbssoftware.com)
* Twitter: [@CrumbsSoftware](https://twitter.com/CrumbsSoftware)

## Downloads
Executables for windows, mac, examples, etc: [https://github.com/ragomusic/crumbs/releases](https://github.com/ragomusic/crumbs/releases)



## What is Crumbs?
Crumbs is a cross platform application designed to easily navigate and search collections of documents. The files of interest are stored as pdf documents (for ease of visualization), and a text only version is created for ease of search.



## Motivation:
I created the initial version of crumbs back in 2013 to help navigate the large amount of information for the discrimination and retaliation case my wife has against University of Chicago Medical Center (Artunduaga v. The University of Chicago Medical Center, No. 1:2012cv08733 [ ](https://dockets.justia.com/docket/illinois/ilndce/1:2012cv08733/276044/) [https://dockets.justia.com/docket/illinois/ilndce/1:2012cv08733/276044/](https://dockets.justia.com/docket/illinois/ilndce/1:2012cv08733/276044/)), scheduled to go to trial on 1/30/2017.

Although there are several commercial applications used mostly by big attorney firms, they were outside of my price range.

By Open Sourcing this software, I hope to help plaintiffs and their lawyers handle large amounts of data, and find key pieces of evidence which can help your case find its way to trial.

It has worked for us, and I hope it works for you too.

Good luck!  

_-Ricardo Garcia (rago)_

## Features:
* Cross Platform: runs in Mac and Windows (easy to port to linux if desired)
* Run it from a flash drive: The software and documents can be stored in a flash drive and run from there.
* Tested with tens of thousands of documents
* Complex searches using regular expressions
* Integration with excel and other office utilities

![crumbs in windows](/docs/images/crumbs_win.png "Crumbs in Windows")

![crumbs in windows](/docs/images/crumbs_mac.png "Crumbs in Mac")

![crumbs in windows](/docs/images/excel_connection.png "Crumbs Excel Integration")


## Example and how to use:
The example can be downloaded as a zip file from [https://github.com/ragomusic/crumbs/releases](https://github.com/ragomusic/crumbs/releases).  It contains executables (mac and windows) and a small database with a subset of emails from the infamous Enron dataset ( [https://www.cs.cmu.edu/~./enron/](https://www.cs.cmu.edu/~./enron/))

Crumbs looks by default for details on how the files are organized in its ini file: crumbs2.ini

**Ini file:**

```
[GENERAL]
DatabaseFile=crumbs2.db3
TableCount=1

[TABLE1]
TableName=ENRON
PathPDF=ENRON/pdf
PathTXT=ENRON/txt
DocumentRoot=ENR
DBtable=ENRONfiles
```

The sections of the ini file:

* [GENERAL]
* DatabaseFile= _name of the sqlite database_
* TableCount= _number of tables_

* [TABLE1] _for each table have one of these, with their number at the end_
* TableName= _Friendly name of table to be shown on Crumbs_
* PathPDF= _Path to root of pdf files_
* PathTXT= _Path to root of txt files_
* DocumentRoot= _Prefix for all the documents in this table_
* DBtable= _Desired name for this table on sqlite database_



## Files location:
Crumbs expects the ini file to be in the same folder than your CrumbsViewer executable.  The sqlite database fill will also be placed on that folder.

The ini file will point to the root folder for each table pdf and text files. Although these can be in any place in your drive (paths can be absolute), we have had better experience with documents stored in folders at the same level where the CrumbsViere executable is located (as in the example).

Crumbs will crawl ALL the sub folder inside each one of those paths, so, it is recommended to organize your documents in subfolders containing just a portion of them. We found that batches of 1000 work very well.

## How to compile:
See the [compilation notes](./docs/compiling_crumbs.txt) on the docs folder

## License:
_Copyright 2013 Ricardo Garcia (rago)_
_Licensed under the Apache License, Version 2.0 (the &quot;License&quot;);_
_you may not use this file except in compliance with the License._
_You may obtain a copy of the License at_
_    http://www.apache.org/licenses/LICENSE-2.0_
_Unless required by applicable law or agreed to in writing, software_
_distributed under the License is distributed on an &quot;AS IS&quot; BASIS,_
_WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied._
_See the License for the specific language governing permissions and_
_limitations under the License._

## Donations and acknowledgments:
After several software developer friends insisted, we caved in and opened a donations button on paypal:

We pledge the proceedings of these (if any) to continue developing and documenting Crumbs. Thanks in advance.

[![Donate](https://img.shields.io/badge/Donate-PayPal-green.svg)](https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&hosted_button_id=S7W7S98PR55PG)



If you use crumbs (as executable from this or other site) for your case, and feel like sharing a note with us, send an email to: _info .at. crumbssoftware . com_

If you create a derivative of Crumbs (follow the license guidelines), feel free to send us a note and share your project.

## Big thanks:
Special thanks to:
* Maria Artunduaga: _For her support, strength, inspiration and drive to make the world a better place, even if it hurts_
* Jamie Franklin: _For all her feedback. Best alpha tester ever_
* Mario Chamorro: _For his expertise with reaching large audiences_
