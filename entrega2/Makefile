
texfile = RetamalesP202173650
bibfile = Referencias.bib

documento: $(texfile).tex $(bibfile)
	latex $(texfile).tex
	bibtex $(texfile).aux
	bibtex $(texfile).aux
	latex $(texfile).tex
	dvipdfmx $(texfile).dvi

clean:
	rm -f *~
	rm -f $(texfile).aux
	rm -f $(texfile).bbl
	rm -f $(texfile).blg
	rm -f $(texfile).dvi
	rm -f $(texfile).log
	rm -f $(texfile).out
	rm -f $(texfile).spl
	rm -f $(texfile).pdf
	rm -f $(texfile)-blx.bib
	rm -f $(texfile).fdb_latexmk
	rm -f $(texfile).fls
	rm -f $(texfile).run.xml
	rm -f $(texfile).synctex.gz
	rm -f $(texfile).tex.backup
	rm -f $(bibfile).backup
