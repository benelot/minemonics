% `ETHbeamerclass.cls'
%  Copyright 2014 by 
%  Dr. Antonios Garas,
%  Chair of Systems Design, ETH Zurich
%  Weinbergstrasse 56/58 CH-8092 Zurich
%
% This class can be redistributed and/or modified under the terms
% of the GNU Public License, version 2.
%
% This is a style file for creating LaTeX beamer presentations
% in the ETH-wide corporate design. 
%
%--------------------------------------------------------------------

\NeedsTeXFormat{LaTeX2e}
\ProvidesClass{ETHbeamerclass}[2014/05/07 v1.0]

%% --- Declaration of options ---
\DeclareOption*{\PassOptionsToClass{\CurrentOption}{beamer}}

%% --- Execution of options ---
\ProcessOptions
\LoadClass{beamer}

\RequirePackage{ifthen}
\usepackage{pifont}

\newif\ifbeamer@secheader
\beamer@secheaderfalse

\newif\ifbeamer@tree@showhooks
\beamer@tree@showhookstrue

\newsavebox\descripbox
\newsavebox\partialbox
\newcommand\vtruncate[2]{%
\setbox\descripbox\vbox{{#2\par}}%
\setbox\partialbox\vsplit\descripbox to #1\relax
\vtop{\unvbox\partialbox}%
}

\setbeamersize{text margin left=0.7cm,text margin right=0.65cm}

\DeclareOption{Helv}{ % Use Helvetica fonts
  \renewcommand{\familydefault}{phv}
  \renewcommand{\sfdefault}{phv}
}
% Declaration of ETH color schemes
\DeclareOption{ETH1}{
 \def \ETHBG {ETH-BG/ETHbackground-ETH1.pdf}
 \def \ethcol {31,64,122}
}
\DeclareOption{ETH2}{
 \def \ETHBG {ETH-BG/ETHbackground-ETH2.pdf}
 \def \ethcol {72,90,44}
}
\DeclareOption{ETH3}{
 \def \ETHBG {ETH-BG/ETHbackground-ETH3.pdf}
 \def \ethcol {18,105,176}
}
\DeclareOption{ETH4}{
 \def \ETHBG {ETH-BG/ETHbackground-ETH4.pdf}
 \def \ethcol {114,121,28}
}
\DeclareOption{ETH5}{
 \def \ETHBG {ETH-BG/ETHbackground-ETH5.pdf}
 \def \ethcol {145,5,106}
}
\DeclareOption{ETH6}{
 \def \ETHBG {ETH-BG/ETHbackground-ETH6.pdf}
 \def \ethcol {111,111,100}
}
\DeclareOption{ETH7}{
 \def \ETHBG {ETH-BG/ETHbackground-ETH7.pdf}
 \def \ethcol {168,50,45}
}
\DeclareOption{ETH8}{
 \def \ETHBG {ETH-BG/ETHbackground-ETH8.pdf}
 \def \ethcol {0,122,150}
}
\DeclareOption{ETH9}{
 \def \ETHBG {ETH-BG/ETHbackground-ETH9.pdf}
 \def \ethcol {149,96,19}
}
\ProcessOptions\relax


\newcommand{\totalframes}{}
\newcommand{\normalbg}{\includegraphics[width=\paperwidth,page=2]{\ETHBG}}
\newcommand{\firstbg}{\normalbg}
\newcommand{\normalfooter}{%
 \leavevmode
    \vskip-1.5cm
    \begin{beamercolorbox}[wd=\paperwidth,ht=0.77cm,dp=0.05cm,%
      leftskip=.55cm,rightskip=.55cm plus1fil]{}
      \fontsize{6pt}{7pt}\selectfont \insertinstitute %}
      \hspace*{0.5cm} \insertauthor \hfill \hspace*{0.05cm} \event \hspace*{0.05cm} \place \hspace*{0.05cm} \vrule{} \hspace*{0.05cm} \insertshortdate{} \hspace*{0.05cm}\vrule{}\hspace*{0.05cm} \insertframenumber{} / \inserttotalframenumber\hspace*{0.05cm}
   \end{beamercolorbox}
}
\newcommand{\firstfooter}{

\leavevmode
  \vskip-1.5cm
    \begin{beamercolorbox}[wd=\paperwidth,ht=0.77cm,dp=0.05cm,%
      leftskip=.55cm,rightskip=.55cm plus1fil]{}
      \fontsize{6pt}{7pt}\selectfont \insertinstitute \hspace*{2em}%}
   \end{beamercolorbox}
}
\newcommand{\navsymb}{\setbeamertemplate{navigation symbols}{}}
\newcommand{\usespecialtitlepagetemplate}{

\newcommand{\normalheader}{%
\leavevmode
    \begin{beamercolorbox}[wd=\paperwidth,ht=0.8cm,%
      leftskip=5.18cm,rightskip=.3cm plus1fil]{}
      \usebeamerfont{section in head/foot}%
    \end{beamercolorbox}

}
\newcommand{\firstheader}{
\leavevmode
    \begin{beamercolorbox}[wd=\paperwidth,ht=1.cm,%
      leftskip=5.18cm,rightskip=.3cm plus1fil]{}
      \usebeamerfont{section in head/foot}%
    \end{beamercolorbox}
}

\makeatletter
\setbeamertemplate{title page}%{default}[1][]
{ \vskip 5.5cm
  \begin{beamercolorbox}[wd=0.98\paperwidth,ht=2ex,dp=1mm,sep=2.5ex,left,shadow=true]{title}
    \usebeamerfont{title}\usebeamercolor[white]{title}\textbf{\inserttitle}\par%
    \ifx\insertsubtitle\@empty%
    \else%
      \vskip0.25cm%
      {\usebeamerfont{subtitle}\usebeamercolor[white]{subtitle}\insertsubtitle\par}%
    \fi%  
 \end{beamercolorbox}%
  
\setbeamertemplate{headline}
{%
\begin{beamercolorbox}{institute}
\insertinstitute{0.9\paperwidth}
\end{beamercolorbox}%
}
 {\usebeamercolor[white]{titlegraphic}\inserttitlegraphic\par}
   \vskip1em
   \begin{beamercolorbox}[wd=0.98\paperwidth,ht=1em,dp=1mm,sep=2.5ex,left,shadow=true]{author}
     \usebeamercolor[white]{author}\usebeamerfont{author}{\textbf \insertauthor}
   \end{beamercolorbox}
   \begin{beamercolorbox}[wd=0.98\paperwidth,ht=2em,dp=2mm,sep=2.5ex,left,shadow=true]{author}
    \usebeamercolor[white]{author}\usebeamerfont{author}\collaborators
  \end{beamercolorbox}\vskip1.5em
 \vfill
}
\makeatother
}

\DeclareOption{totalframes}{\renewcommand{\totalframes}{/\inserttotalframenumber}}
\DeclareOption{first}{
  \renewcommand{\firstbg}{\includegraphics[width=\paperwidth,page=1]{\ETHBG}}
  \usespecialtitlepagetemplate
}
\DeclareOption{firstalt}{
  \renewcommand{\firstbg}{\includegraphics[width=\paperwidth,page=2]{\ETHBG}}
  \usespecialtitlepagetemplate
}
\DeclareOption{aspectratio=169}{
  \renewcommand{\firstbg}{\includegraphics[width=\paperwidth,page=3]{\ETHBG}}
  \renewcommand{\normalbg}{\includegraphics[width=\paperwidth,page=4]{\ETHBG}}
  \PassOptionsToClass{\CurrentOption}{beamer}
  \setbeamersize{text margin left=.9cm,text margin right=0.65cm}
}

\DeclareOption{navigation}{\renewcommand{\navsymb}{}}
\DeclareOption{firstsupp}{\renewcommand{\firstfooter }{}}
\DeclareOption{lastsupp}{\renewcommand{\lastfooter}{}}

% execute options
\ProcessOptions

% inkove command for navigation symbols - use empty template by default
\navsymb

\setbeamertemplate{footline}
{%
\ifthenelse{\equal{\insertframenumber}{1}}{%
    \firstfooter%
  }{%
    \normalfooter%
  }
}

\setbeamertemplate{headline}
{%
\ifthenelse{\equal{\insertframenumber}{1}}{%
    \firstheader%
  }{%
    \normalheader%
  }
}

% Frametitle position each slide
\setbeamertemplate{frametitle} { \textbf{\usebeamercolor[black]{frametitle}\insertframetitle} \par}

\usebackgroundtemplate{
  \ifthenelse{\equal{\insertframenumber}{1}}{%
    \firstbg%
  }{%
    \normalbg%
  }
}

\mode<presentation>
{
  \useoutertheme{default}   % empty
}


%---------------------------------------------------------------%
\definecolor{colorSG}{RGB}{\ethcol}  %% This is the ETH7 color
\definecolor{colorSG.fg}{rgb}{\ethcol}  %% This is the ETH7 color
\usecolortheme[RGB={\ethcol}]{structure}
\definecolor{black}{RGB}{0,0,0}
\definecolor{white}{RGB}{255,255,255}

%---------------------------------------------------------------%
\setbeamercolor{block title}{use=colorSG,fg=colorSG.fg,bg=colorSG.fg!20!bg}
\setbeamercolor{block title alerted}{use=alerted text,fg=alerted text.fg,bg=alerted text.fg!20!bg}
\setbeamercolor{block title example}{use=example text,fg=example text.fg,bg=example text.fg!20!bg}
\setbeamercolor{block body}{parent=normal text,use=block title,bg=block title.bg!50!bg}
\setbeamercolor{block body alerted}{parent=normal text,use=block title alerted}
\setbeamercolor{block body example}{parent=normal text,use=block title example}
\setbeamercolor{normal text}{fg=black,bg=white}
\setbeamercolor{alerted text}{fg=colorSG}

\setbeamertemplate{block begin}{
  \setlength{\leftmargini}{0.55cm}
   \vskip.75ex
   \begin{beamercolorbox}[sep=.75ex]{block title}%
     \usebeamerfont*{block title}\insertblocktitle
   \end{beamercolorbox}%
   {\ifbeamercolorempty[bg]{block body}{}{\nointerlineskip\vskip-0.5pt}}%
   \usebeamerfont{block body}%
   \begin{beamercolorbox}[sep=.75ex,vmode]{block body}%
     \ifbeamercolorempty[bg]{block body}{\vskip-.25ex}{\vskip-.75ex}\vbox{}%
   }
   \setbeamertemplate{block end}{
   \end{beamercolorbox}
}
  
%%modify itemize
\setbeamertemplate{itemize items}[square]
\setbeamertemplate{enumerate items}[square]
\setbeamertemplate{sections/subsections in toc}[square]

\setlength\leftmargini  {0.2cm}
\setlength\leftmarginii  {0.4cm}
\setlength\leftmarginiii  {0.4cm}
\setlength  \labelsep  {0.5em}
\setlength  \itemsep {1.5ex} 
\setlength  \labelwidth{\leftmargini}
\addtolength\labelwidth{-\labelsep}

\mode
<all>
%%
%% End of file