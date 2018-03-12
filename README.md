###tgs_2pass pipeline

question and method
1. 由于某些exon检测的并不准确，对一些明显有问题的alignment，采用RNA aligner的算法，然后根据alignment的结果对exon splice junction site进行修正
2. left-extension 的问题，当前anchor能够extension到哪个位置，要综合考虑其他exon的位置信息; 同理还有right-alignment的问题。
3. check_cigar function完成，对于alignment有误的进行修正(例如，'N'左右两侧的操作为'I'或者'D'，并且长度不是很小)
