# Hexdump

This is a hexdump utility as simple as it gets.

### File Example
```
hexdump -f=file.exe
hexdump "-f=file with spaces.exe"
```

### Direct Input Example
```
hexdump -t=Text
hexdump "-t=Text with spaces"
```

### Piping Example
``` 
ipconfig | hexdump
```

### Sample Output
```
Offset(h)  00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F 

00000000   4C 6F 72 65 6D 20 69 70 73 75 6D 20 64 6F 6C 6F      Lorem.ipsum.dolo
00000010   72 20 73 69 74 20 61 6D 65 74 2C 20 63 6F 6E 73      r.sit.amet,.cons
00000020   65 63 74 65 74 75 72 20 61 64 69 70 69 73 63 69      ectetur.adipisci
00000030   6E 67 20 65 6C 69 74 2C 20 73 65 64 20 64 6F 20      ng.elit,.sed.do.
00000040   65 69 75 73 6D 6F 64 20 74 65 6D 70 6F 72 20 69      eiusmod.tempor.i
00000050   6E 63 69 64 69 64 75 6E 74 20 75 74 20 6C 61 62      ncididunt.ut.lab
00000060   6F 72 65 20 65 74 20 64 6F 6C 6F 72 65 20 6D 61      ore.et.dolore.ma
00000070   67 6E 61 20 61 6C 69 71 75 61 2E 20 55 74 20 65      gna.aliqua..Ut.e
00000080   6E 69 6D 20 61 64 20 6D 69 6E 69 6D 20 76 65 6E      nim.ad.minim.ven
00000090   69 61 6D 2C 20 71 75 69 73 20 6E 6F 73 74 72 75      iam,.quis.nostru
000000A0   64 20 65 78 65 72 63 69 74 61 74 69 6F 6E 20 75      d.exercitation.u
000000B0   6C 6C 61 6D 63 6F 20 6C 61 62 6F 72 69 73 20 6E      llamco.laboris.n
000000C0   69 73 69 20 75 74 20 61 6C 69 71 75 69 70 20 65      isi.ut.aliquip.e
000000D0   78 20 65 61 20 63 6F 6D 6D 6F 64 6F 20 63 6F 6E      x.ea.commodo.con
000000E0   73 65 71 75 61 74 2E 20 44 75 69 73 20 61 75 74      sequat..Duis.aut
000000F0   65 20 69 72 75 72 65 20 64 6F 6C 6F 72 20 69 6E      e.irure.dolor.in
00000100   20 72 65 70 72 65 68 65 6E 64 65 72 69 74 20 69      .reprehenderit.i
00000110   6E 20 76 6F 6C 75 70 74 61 74 65 20 76 65 6C 69      n.voluptate.veli
00000120   74 20 65 73 73 65 20 63 69 6C 6C 75 6D 20 64 6F      t.esse.cillum.do
00000130   6C 6F 72 65 20 65 75 20 66 75 67 69 61 74 20 6E      lore.eu.fugiat.n
00000140   75 6C 6C 61 20 70 61 72 69 61 74 75 72 2E 20 45      ulla.pariatur..E
00000150   78 63 65 70 74 65 75 72 20 73 69 6E 74 20 6F 63      xcepteur.sint.oc
00000160   63 61 65 63 61 74 20 63 75 70 69 64 61 74 61 74      caecat.cupidatat
00000170   20 6E 6F 6E 20 70 72 6F 69 64 65 6E 74 2C 20 73      .non.proident,.s
00000180   75 6E 74 20 69 6E 20 63 75 6C 70 61 20 71 75 69      unt.in.culpa.qui
00000190   20 6F 66 66 69 63 69 61 20 64 65 73 65 72 75 6E      .officia.deserun
000001A0   74 20 6D 6F 6C 6C 69 74 20 61 6E 69 6D 20 69 64      t.mollit.anim.id
000001B0   20 65 73 74 20 6C 61 62 6F 72 75 6D 2E               .est.laborum.
```
