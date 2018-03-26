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


dataset_sim_dm_g2as运行结果比较：
1. tgs_2pass: 
good alignment: 11839; correct alignment: 2730; hit all: 9516

1.1 tgs_2pass_waitlen: 
good alignment: 11851; correct alignment: 2738; hit all: 9545  （the main reason for hit all is the left and right ext）

1.2 left and right ext:
good alignment: 11616; correct alignment: 2736; hit all: 10290 

1.3 left and right ext adding splice_offset
good alignment: 11702; correct alignment: 2813; hit all: 10254 

1.4 left and right ext adding splice_offset and judge the key of first and last anchor for filtering
 (splicedistance = 100000) : good alignment: 11722; correct alignment: 2814; hit all: 10253
 (splicedistance = 100000， thre  30) : good alignment: 11776; correct alignment: 2820; hit all: 10108 （ignor）
 (splicedistance = 200000) : good alignment: 11709; correct alignment: 2790; hit all: 10273 (ignore)
 (splicedistance = 200000, thre = 30) : good alignment: 11784; correct alignment: 2820; hit all: 10132
 (splicedistance = 200000, thre = 20) : good alignment: 11755; correct alignment: 2813; hit all: 10222

2. tgs_1pass:
 (splicedistance = 100000) : good alignment: 11815; correct alignment: 2774; hit all: 9402
 (splicedistance = 200000) : good alignment: 11769; correct alignment: 2769; hit all: 9465
3. minimap2.6: 
good alignment: 11725; correct alignment: 2660; hit all: 9051
4. gmap
hit all: 9872  







qlen 和 tlen的长度差计算公式:

*tlen - qlen = tlen\*error_rate\* (error_rate_deletion/error_rate - error_rate_insertion/error_rate)\*average_len_of_deletion*

对于ONT 2D一般：
error_rate = 13.4%, error_rate_deletion/error_rate = 35.70%, error_rate_insertion/error_rate = 23.30%, average_len_of_deletion = 3bp

ref: Comprehensive comparison of Pacific Biosciences and Oxford Nanopore Technologies and their applications to transcriptome analysis


×××××××××××××××××
可能存在bug的一些地方：
1. 对于splice_distance = 100000的问题。由于在merge_anchor的过程中去掉了一些anchor，导致两个anchor之间的距离大于splice_distance.(可以解决)

**Process_pbsim_data** 有问题，需要改正

