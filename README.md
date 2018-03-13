###tgs_2pass pipeline

question and method
1. 由于某些exon检测的并不准确，对一些明显有问题的alignment，采用RNA aligner的算法，然后根据alignment的结果对exon splice junction site进行修正
2. left-extension 的问题，当前anchor能够extension到哪个位置，要综合考虑其他exon的位置信息; 同理还有right-alignment的问题。
3. check_cigar function完成，对于alignment有误的进行修正(例如，'N'左右两侧的操作为'I'或者'D'，并且长度不是很小)(S42_2为例)
4. 调整merge anchor的条件，不再是有overlap则merge，当overlap的长度多于一半的时候进行merge
5. 修正一下local_hash_anchor() 中qlen1, qlen2的计算方式， anchor 选择方式


未进行第一步结果：(500 reads)
- good alignment: 477; correct alignment: 193; hit all: 403
进行第一步结果：(500 reads) first
- good alignment: 475; correct alignment: 195; hit all: 402
进行第一步结果：(500 reads) second
- good alignment: 479; correct alignment: 201; hit all: 396
进行第一步结果：(500 reads) third ,adjust the gap and extension score same to DNA aligner
- good alignment: 495; correct alignment: 213; hit all: 397
进行第一步结果：(500 reads) fouth ,adjust the binary_search_anchor() function, and solve the bug
- good alignment: 494; correct alignment: 213; hit all: 406
进行第四步结果：(500 reads)
- good alignment: 495; correct alignment: 215; hit all: 406
