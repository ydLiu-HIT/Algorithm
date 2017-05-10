data<-read.csv('time.txt',sep='\t')

plot(data$V1,data$V2,col="red",pch=22,bg="yellow", xlim=c(2,20),lwd=2,xlab="vertexNum",ylab="Time/ms",type="b",main="不同搜索算法的性能曲线")
lines(data$V1,data$V3,col="green",pch=16,bg="yellow",lwd=2,xlab="vertexNum",ylab="Time/ms",type="b",lty=2)
lines(data$V1,data$V4,col="blue",pch=17,bg="yellow",lwd=2,xlab="vertexNum",ylab="Time/ms",type="b",lty=2)
legend("topleft",legend=c("dfs","bfs","hillclimb"),pch=c(22,16,17),col=c("red","green","blue"),lwd=2)
