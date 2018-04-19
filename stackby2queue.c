#include <stdio.h>
#include "seqqueue.h"

typedef struct StackBy2Queue{
    SeqQueue queue1;
    SeqQueue queue2;
} StackBy2Queue;

//初始化
void StackInit(StackBy2Queue* stack){
    if(stack==NULL){
        return;
    }
    SeqQueueInit(&stack->queue1);
    SeqQueueInit(&stack->queue2);
}

//入栈
void StackPush(StackBy2Queue* stack,SeqQueueType value){
    if(stack==NULL){
        return;
    }
    //判断谁为空，谁不为空，入队列，取非空队列进行插入
    SeqQueue* input=NULL;
    if(stack->queue1.size!=0){
        input=&stack->queue1;
    }
    input=&stack->queue2;
    SeqQueuePush(input,value); 
}

//出栈
void StackPop(StackBy2Queue* stack){
    if(stack==NULL){
        return;
    }
    //将当前非空的队列里的元素搬运到空队列中，只剩一个元素时，就是要出栈的元素
    if(stack->queue1.size==0&&stack->queue2.size==0){
        //空栈
        return;
    }
    //确定谁是非空的栈（from），谁是空栈（to）
    //是将from中的元素像to中转移至最后一个
    SeqQueue* from=NULL;
    SeqQueue* to=NULL;
    if(stack->queue1.size!=0){
        from=&stack->queue1;
        to=&stack->queue2;
    }
    else{
        from=&stack->queue2;
        to=&stack->queue1;
    }
    while(1){
        if((*from).size==1){
            //此时队列中已经只剩一个元素，就是要出栈的元素
            break;
        }
        //从from中取队首元素，删除pop掉，插入push to中
        SeqQueueType top;
        SeqQueueTop(from,&top);
        SeqQueuePop(from);
        SeqQueuePush(to,top);
    }
    //把最后剩的那个元素删除掉，出栈完毕
    SeqQueuePop(from);
}

//取栈顶元素
int StackTop(StackBy2Queue* stack,SeqQueueType* top){
    //栈顶元素就是非空队列的第一个元素
    if(stack==NULL){
        return 0;
    }
    if(stack->queue1.size==0&&stack->queue2.size==0){
        return 0;
    }
    if(stack->queue1.size!=0){
        SeqQueueTop(&stack->queue1,top);
        return 1;
    }
    else{
        SeqQueueTop(&stack->queue2,top);
        return 1;
    }
}

void StackPrint(StackBy2Queue* stack,const char* msg){
    if(stack==NULL){
        return;
    }
    printf("============== queue1 ===============\n");
    SeqPrintChar(&stack->queue1,msg);

    printf("============== queue2 ===============\n");
    SeqPrintChar(&stack->queue2,msg);
}

void TestStack(){
    printf("================= %s ==============\n",__FUNCTION__);
    StackBy2Queue stack;
    StackInit(&stack);

    StackPush(&stack,'1');
    StackPush(&stack,'2');
    StackPush(&stack,'3');
    StackPush(&stack,'4');
    StackPrint(&stack,"测试入栈四个元素");

    StackPop(&stack);
    StackPrint(&stack,"测试出栈一个元素");
    StackPop(&stack);
    StackPrint(&stack,"测试出栈2个元素");
    
    SeqQueueType top;
    int ret=StackTop(&stack,&top);
    printf("测试取栈顶元素\n");
    printf("返回值为：%d ，栈顶元素是：%c\n",ret,top);
}

void main(){
    TestStack();
}
