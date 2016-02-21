#! /bin/sh
pdflatex main.tex
biber main.bcf
pdflatex main.tex
mv main.toc main.thm main.tdo main.run.xml main.out main.lot main.log main.lof main.bcf main.aux main.blg main.bbl main.pdf --target-directory=build
evince build/main.pdf&
