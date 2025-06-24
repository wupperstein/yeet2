default:
	g++ -ggdb -Wl,--no-as-needed `root-config --libs --ldflags` `root-config --cflags` analysis.C -o drifttime
	g++ -ggdb -Wl,--no-as-needed `root-config --libs --ldflags` `root-config --cflags` analysis.C -o wirecorr -DWIRECORR
	g++ -ggdb -Wl,--no-as-needed `root-config --libs --ldflags` `root-config --cflags` analysis.C -o evenwire -DEVENWIRECORR
	g++ -ggdb -Wl,--no-as-needed `root-config --libs --ldflags` `root-config --cflags` analysis.C -o unevenwire -DUNEVENWIRECORR
	g++ -ggdb -Wl,--no-as-needed `root-config --libs --ldflags` `root-config --cflags` analysis.C -o neighbor -DNEIGHBORWIRECORR

neighborhood:
	g++ -ggdb -Wl,--no-as-needed `root-config --libs --ldflags` `root-config --cflags` analysis.C -o neighbor -DNEIGHBORWIRECORR
	g++ -ggdb -Wl,--no-as-needed `root-config --libs --ldflags` `root-config --cflags` analysis.C -o neighboreven -DNEIGHBOREVEN
	g++ -ggdb -Wl,--no-as-needed `root-config --libs --ldflags` `root-config --cflags` analysis.C -o neighboruneven -DNEIGHBORUNEVEN

neighborhood2d:
	g++ -ggdb -Wl,--no-as-needed `root-config --libs --ldflags` `root-config --cflags` analysis.C -o neighboreven2d -DNEIGHBOREVEN2D
	g++ -ggdb -Wl,--no-as-needed `root-config --libs --ldflags` `root-config --cflags` analysis.C -o neighboruneven2d -DNEIGHBORUNEVEN2D

loc:
	g++ -ggdb -Wl,--no-as-needed `root-config --libs --ldflags` `root-config --cflags` ana1.C -o wire2d -DWIRE_2D
	g++ -ggdb -Wl,--no-as-needed `root-config --libs --ldflags` `root-config --cflags` ana1.C -o wire1d -DWIRE_1D

tot:
	g++ -ggdb -Wl,--no-as-needed `root-config --libs --ldflags` `root-config --cflags` tot.C -o tot2d -DTOT_2D
	g++ -ggdb -Wl,--no-as-needed `root-config --libs --ldflags` `root-config --cflags` tot.C -o tot1d -DTOT_1D

filter:
	g++ -ggdb -Wl,--no-as-needed `root-config --libs --ldflags` `root-config --cflags` tot.C -o tot2df -DTOT_2D -DFILTERED
	g++ -ggdb -Wl,--no-as-needed `root-config --libs --ldflags` `root-config --cflags` tot.C -o tot1df -DTOT_1D -DFILTERED
	g++ -ggdb -Wl,--no-as-needed `root-config --libs --ldflags` `root-config --cflags` tot.C -o wdfilt -DWIRECORR

newdrift:
	g++ -ggdb -Wl,--no-as-needed `root-config --libs --ldflags` `root-config --cflags` tot.C -o driftfilter

first15:
	g++ -ggdb -Wl,--no-as-needed `root-config --libs --ldflags` `root-config --cflags` analysis.C -o wirecorr12 -DWIRECORRSTART

abstand:
	g++ -ggdb -Wl,--no-as-needed `root-config --libs --ldflags` `root-config --cflags` abstand.C -o dist20
	g++ -ggdb -Wl,--no-as-needed `root-config --libs --ldflags` `root-config --cflags` abstand.C -o dist5 -DFIVEDEGREES
	g++ -ggdb -Wl,--no-as-needed `root-config --libs --ldflags` `root-config --cflags` abstand.C -o dist10 -DTENDEGREES
	g++ -ggdb -Wl,--no-as-needed `root-config --libs --ldflags` `root-config --cflags` abstand.C -o dist45 -DFORTYFIVEDEGREES
	g++ -ggdb -Wl,--no-as-needed `root-config --libs --ldflags` `root-config --cflags` abstand.C -o dist60 -DSIXTYDEGREES
	g++ -ggdb -Wl,--no-as-needed `root-config --libs --ldflags` `root-config --cflags` abstand.C -o dist90 -DNINTYDEGREES	
	g++ -ggdb -Wl,--no-as-needed `root-config --libs --ldflags` `root-config --cflags` abstand.C -o distwire -DWIREDISC
	g++ -ggdb -Wl,--no-as-needed `root-config --libs --ldflags` `root-config --cflags` abstand.C -o dist1020 -DTENTWENTY
	g++ -ggdb -Wl,--no-as-needed `root-config --libs --ldflags` `root-config --cflags` abstand.C -o dist2030 -DTWENTYTHIRTY
	g++ -ggdb -Wl,--no-as-needed `root-config --libs --ldflags` `root-config --cflags` abstand.C -o dist3040 -DTHIRTYFORTY
	g++ -ggdb -Wl,--no-as-needed `root-config --libs --ldflags` `root-config --cflags` abstand.C -o dist4060 -DFORTYSIXTY
	g++ -ggdb -Wl,--no-as-needed `root-config --libs --ldflags` `root-config --cflags` abstand.C -o dist6090 -DSIXTYNINTY


zw:
	g++ -ggdb -Wl,--no-as-needed `root-config --libs --ldflags` `root-config --cflags` abstand.C -o dist20


winkelv:
	g++ -ggdb -Wl,--no-as-needed `root-config --libs --ldflags` `root-config --cflags` winkelverteilung.C -o wink2
	g++ -ggdb -Wl,--no-as-needed `root-config --libs --ldflags` `root-config --cflags` W.C -o wink
	g++ -ggdb -Wl,--no-as-needed `root-config --libs --ldflags` `root-config --cflags` W.C -o winkeven -DGRADE
	g++ -ggdb -Wl,--no-as-needed `root-config --libs --ldflags` `root-config --cflags` W.C -o winkuneven -DUNGRADE

unfiltered:
	g++ -ggdb -Wl,--no-as-needed `root-config --libs --ldflags` `root-config --cflags` analysis.C -o unfiltered -DUNFILTERED

all: default neighborhood neighborhood2d loc tot filter newdrift first15 abstand winkelv

clean:
	rm -f drifttime wirecorr evenwire unevenwire neighbor neighboreven neighboruneven neighboreven2d neighboruneven2d wire2d wire1d tot2d tot1d
	rm -f tot2df tot1df wdfilt driftfilter wirecorr12 dist wink wink2
