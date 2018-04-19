stackby2queue:stackby2queue.c seqqueue.c
	gcc $^ -g -o $@

.PHONY:clean
	clean:
		rm -f stackby2queue
