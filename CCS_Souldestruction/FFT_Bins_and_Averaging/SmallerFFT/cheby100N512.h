Int16 chebwin512[512] = {
36, //1
10, //2
12, //3
14, //4
15, //5
17, //6
20, //7
22, //8
24, //9
27, //10
30, //11
33, //12
36, //13
40, //14
44, //15
48, //16
52, //17
57, //18
62, //19
67, //20
73, //21
79, //22
85, //23
92, //24
99, //25
107, //26
115, //27
123, //28
132, //29
142, //30
152, //31
162, //32
173, //33
185, //34
197, //35
210, //36
224, //37
238, //38
253, //39
268, //40
285, //41
302, //42
320, //43
338, //44
358, //45
378, //46
399, //47
422, //48
445, //49
469, //50
494, //51
520, //52
547, //53
575, //54
605, //55
635, //56
667, //57
700, //58
734, //59
769, //60
806, //61
844, //62
883, //63
924, //64
966, //65
1010, //66
1055, //67
1102, //68
1150, //69
1200, //70
1251, //71
1304, //72
1359, //73
1415, //74
1473, //75
1533, //76
1595, //77
1658, //78
1724, //79
1791, //80
1860, //81
1932, //82
2005, //83
2080, //84
2157, //85
2237, //86
2318, //87
2402, //88
2488, //89
2576, //90
2666, //91
2758, //92
2853, //93
2950, //94
3049, //95
3151, //96
3255, //97
3362, //98
3470, //99
3582, //100
3696, //101
3812, //102
3931, //103
4052, //104
4176, //105
4302, //106
4431, //107
4563, //108
4697, //109
4833, //110
4973, //111
5115, //112
5259, //113
5406, //114
5556, //115
5709, //116
5864, //117
6022, //118
6182, //119
6345, //120
6511, //121
6679, //122
6850, //123
7024, //124
7200, //125
7379, //126
7561, //127
7745, //128
7932, //129
8121, //130
8313, //131
8507, //132
8704, //133
8904, //134
9106, //135
9310, //136
9517, //137
9726, //138
9937, //139
10151, //140
10367, //141
10586, //142
10806, //143
11029, //144
11254, //145
11481, //146
11710, //147
11941, //148
12174, //149
12409, //150
12646, //151
12885, //152
13126, //153
13368, //154
13612, //155
13857, //156
14104, //157
14353, //158
14603, //159
14854, //160
15106, //161
15360, //162
15615, //163
15871, //164
16128, //165
16386, //166
16645, //167
16905, //168
17165, //169
17426, //170
17687, //171
17950, //172
18212, //173
18475, //174
18738, //175
19001, //176
19264, //177
19527, //178
19790, //179
20053, //180
20316, //181
20578, //182
20840, //183
21101, //184
21362, //185
21622, //186
21881, //187
22139, //188
22396, //189
22652, //190
22907, //191
23160, //192
23412, //193
23663, //194
23912, //195
24159, //196
24405, //197
24648, //198
24890, //199
25130, //200
25368, //201
25603, //202
25836, //203
26066, //204
26294, //205
26520, //206
26743, //207
26963, //208
27180, //209
27394, //210
27605, //211
27813, //212
28017, //213
28219, //214
28417, //215
28611, //216
28802, //217
28989, //218
29173, //219
29353, //220
29529, //221
29700, //222
29868, //223
30032, //224
30192, //225
30347, //226
30498, //227
30645, //228
30787, //229
30925, //230
31058, //231
31186, //232
31310, //233
31429, //234
31543, //235
31653, //236
31758, //237
31857, //238
31952, //239
32041, //240
32126, //241
32206, //242
32280, //243
32349, //244
32413, //245
32472, //246
32525, //247
32573, //248
32616, //249
32654, //250
32686, //251
32713, //252
32735, //253
32751, //254
32762, //255
32767, //256
32767, //257
32762, //258
32751, //259
32735, //260
32713, //261
32686, //262
32654, //263
32616, //264
32573, //265
32525, //266
32472, //267
32413, //268
32349, //269
32280, //270
32206, //271
32126, //272
32041, //273
31952, //274
31857, //275
31758, //276
31653, //277
31543, //278
31429, //279
31310, //280
31186, //281
31058, //282
30925, //283
30787, //284
30645, //285
30498, //286
30347, //287
30192, //288
30032, //289
29868, //290
29700, //291
29529, //292
29353, //293
29173, //294
28989, //295
28802, //296
28611, //297
28417, //298
28219, //299
28017, //300
27813, //301
27605, //302
27394, //303
27180, //304
26963, //305
26743, //306
26520, //307
26294, //308
26066, //309
25836, //310
25603, //311
25368, //312
25130, //313
24890, //314
24648, //315
24405, //316
24159, //317
23912, //318
23663, //319
23412, //320
23160, //321
22907, //322
22652, //323
22396, //324
22139, //325
21881, //326
21622, //327
21362, //328
21101, //329
20840, //330
20578, //331
20316, //332
20053, //333
19790, //334
19527, //335
19264, //336
19001, //337
18738, //338
18475, //339
18212, //340
17950, //341
17687, //342
17426, //343
17165, //344
16905, //345
16645, //346
16386, //347
16128, //348
15871, //349
15615, //350
15360, //351
15106, //352
14854, //353
14603, //354
14353, //355
14104, //356
13857, //357
13612, //358
13368, //359
13126, //360
12885, //361
12646, //362
12409, //363
12174, //364
11941, //365
11710, //366
11481, //367
11254, //368
11029, //369
10806, //370
10586, //371
10367, //372
10151, //373
9937, //374
9726, //375
9517, //376
9310, //377
9106, //378
8904, //379
8704, //380
8507, //381
8313, //382
8121, //383
7932, //384
7745, //385
7561, //386
7379, //387
7200, //388
7024, //389
6850, //390
6679, //391
6511, //392
6345, //393
6182, //394
6022, //395
5864, //396
5709, //397
5556, //398
5406, //399
5259, //400
5115, //401
4973, //402
4833, //403
4697, //404
4563, //405
4431, //406
4302, //407
4176, //408
4052, //409
3931, //410
3812, //411
3696, //412
3582, //413
3470, //414
3362, //415
3255, //416
3151, //417
3049, //418
2950, //419
2853, //420
2758, //421
2666, //422
2576, //423
2488, //424
2402, //425
2318, //426
2237, //427
2157, //428
2080, //429
2005, //430
1932, //431
1860, //432
1791, //433
1724, //434
1658, //435
1595, //436
1533, //437
1473, //438
1415, //439
1359, //440
1304, //441
1251, //442
1200, //443
1150, //444
1102, //445
1055, //446
1010, //447
966, //448
924, //449
883, //450
844, //451
806, //452
769, //453
734, //454
700, //455
667, //456
635, //457
605, //458
575, //459
547, //460
520, //461
494, //462
469, //463
445, //464
422, //465
399, //466
378, //467
358, //468
338, //469
320, //470
302, //471
285, //472
268, //473
253, //474
238, //475
224, //476
210, //477
197, //478
185, //479
173, //480
162, //481
152, //482
142, //483
132, //484
123, //485
115, //486
107, //487
99, //488
92, //489
85, //490
79, //491
73, //492
67, //493
62, //494
57, //495
52, //496
48, //497
44, //498
40, //499
36, //500
33, //501
30, //502
27, //503
24, //504
22, //505
20, //506
17, //507
15, //508
14, //509
12, //510
10, //511
};
