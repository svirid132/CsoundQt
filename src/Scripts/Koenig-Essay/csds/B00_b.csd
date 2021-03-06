<CsoundSynthesizer>

; Id: B00_b.CSD mg (2006, rev.2009)
; author: marco gasperini (marcogsp at yahoo dot it)

; G.M. Koenig
; ESSAY (1957)

<CsOptions>
-W -f -oB00_b.wav
</CsOptions>

<CsInstruments>

sr     = 192000
kr     = 192000
ksmps  = 1
nchnls = 1

;=============================================
; SINUS TONES (S)
;=============================================
	instr 1	
iamp	= ampdb(90+p4)
ifreq	= p5

a1	oscili iamp , ifreq , 1
aenv	linen 1 , .01 , p3 , .005

aout	= a1 * aenv

	out aout
	endin
;=============================================

;=============================================
; FILTERED NOISE (N)
;=============================================
	instr 2
iamp	= ampdb(87+p4)
ifreq	= p5
ibw	= ifreq * .05		; filtered noise's bandwidth 5% of central frequency

a1	rnd31 iamp , 1 
k1	rms a1

afilt	butterbp a1 , ifreq , ibw
afilt	butterbp afilt , ifreq , ibw

aenv	linen .8,  .01 , p3 , .005

aout	gain afilt , k1
aout	= aout * aenv 

	out aout
	endin
;=============================================

;=============================================
; FILTERED IMPULSES (I)
;=============================================
	instr 3
iamp	= ampdb(90+p4)
ifreq	= p5
ibw	= ifreq * .01		; filtered pulse's bandwidth 1% of central frequency

if1	= ifreq-(ibw/3)
if2	= ifreq+((2*ibw)/3)

				
a1	mpulse iamp , 0 

afilt	atonex a1 , if1 , 2
afilt	tonex afilt*90 , if2 , 2
afilt	butterbp afilt*500, ifreq , ibw *.05

aenv	linseg 1 , p3-.005, 1 , .005 , 0

aout	= afilt * aenv 

	out aout*(sr/192000)
	endin
;=============================================

</CsInstruments>
<CsScore>
;functions--------------------------------------------------
f1	0	8192	10	1	; sinusoid
;/functions--------------------------------------------------

t0	4572	; 76.2 cm/sec. tape speed (durations in cm)

;test--------------------------------------------------
;mute-------------------------------------------------
q 1 0 1
q 2 0 1
q 3 0 1
;/mute-------------------------------------------------
;/test-------------------------------------------------

;==================================================
; 120. MATERIAL B
; 121. total length: 256.5 cm, 6 sections
;
; sequence b1
;
; length   sequence 	
; 62.5  cm (5)
; 18.5  cm (2)
; 12.3  cm (1)
;
; sequence b2
;
; length   sequence 	
; 41.7  cm (4)
; 93.7  cm (6)
; 27.8  cm (3)

;==================================================

;************************************************** b1
;==================================121.21
; 62.5 cm ratio 8/7
;----------------------------------------
;			p4	p5
;			iamp	ifreq	timbre
;			[dB]	[Hz]
i2	0	10.4	-5	6400	; R
i2	+	7	-5	4032    ; R
i2	+	9.1	-5	5702    ; R
i2	+	5.3	-5	2540    ; R
i2	+	6.1	-5	3592    ; R
i2	+	8	-5	1600    ; R
i1	45.9	11.9	-3	5080    ; S
i2	57.8	4.7	-5	2263    ; R
s                                   
t0	4572	
;==================================121.22
; 18.5 cm ratio 11/10
;----------------------------------------
i2	0	1.9	-4	1008	; R
i2	+	3.2	-4	3200    ; R
i1	5.1	1.8	-2	1426    ; S
i1	+	2.6	-2	4526    ; S
i2	9.5	2.9	-4	635     ; R
i2	+	1.6	-4	2016    ; R
i1	14	2.1	0	898     ; S
i1	+	2.4	0	2851    ; S
s                                   
t0	4572	
;==================================121.23
; 12.3 cm ratio 12/11
;----------------------------------------
i1	0	1.4	0	1270	; S
i2	1.4	1.1	-3	566     ; R
i1	2.5	1.3	0	1796    ; S
i1	+	1.9	0	800     ; S
i1	+	2.1	0	1131    ; S
i1	+	1.2	0	504     ; S
i1	+	1.6	0	713     ; S
i1	+	1.6	0	449     ; S
s                                   
;************************************************** b2
;==================================121.24
; 41.7 cm ratio 9/8
;----------------------------------------
t0	4572	
i2	0	6	-3	400	; R
i2	+	4.2	-3	635	; R
i2	+	5.3	-3	449     ; R
i1	15.5	3.3	-3	1008    ; S
i2	18.8	3.8	-3	713     ; R
i2	+	4.7	-3	1600    ; R
i1	27.3	6.8	-3	504     ; S
i1	+	7.6	-3	1131    ; S
s                                   
t0	4572	
;==================================121.25
; 93.7 cm ratio 7/6
;----------------------------------------
i2	0	6.4	-3	2540	; R
i1	6.4	13.9	-3	800     ; S
i1	+	18.9	-3	1796    ; S
i1	+	10.2	-3	566     ; S
i1	+	11.9	-3	4032    ; S
i1	+	16.2	-3	1270    ; S
i1	+	7.5	-3	2851    ; S
i3	85	8.7	11.5	898     ; I
s                                   
t0	4572	
;==================================121.26
; 27.8 cm ratio 10/9
;----------------------------------------
i1	0	2.6	-3	2016	; S
i1	+	4.4	-3	4526    ; S
i3	7	2.3	7.5	1426    ; I
i3	+	3.6	1	3200    ; I
i1	12.9	3.9	-3	2263    ; S
i3	16.8	4.9	-2.5	5080    ; I
i3	+	2.9	0	3592    ; I
i3	+	3.2	-3	5702    ; I
                                    
; total length: 256.5 cm
e

</CsScore>
</CsoundSynthesizer>