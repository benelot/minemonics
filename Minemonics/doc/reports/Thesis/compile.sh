#! /bin/sh
pdflatex main.tex
biber main.bcf
pdflatex main.tex
