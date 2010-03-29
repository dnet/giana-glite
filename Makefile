TESTFREQ=44100
TESTSEQ=$(shell ./seqgen.py)

localtest: output.wav
	mplayer $<

output.wav: wavdata.bin wavhdr.sh wavhdr.c
	./wavhdr.sh $(TESTFREQ)

wavdata.bin: wavgen.sh wavgen.c
	./wavgen.sh $(TESTFREQ) $(TESTSEQ)

clean:
	rm -f output.wav wavhdr wavgen wavdata.bin compile.log

.PHONY: clean localtest
