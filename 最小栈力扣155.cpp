//class MinStack { /* * 思路：每次入栈2个元素，一个是入栈的元素本身，一个是当前栈元素的最小值 * 如：入栈序列为2-3-1，则入栈后栈中元素序列为：2-2-3-2-1-1 * 用空间代价来换取时间代价 */ private Stack<Integer> stack;


public MinStack() 
{
    stack = new Stack<Integer>();
}

public void push(int x) {
    if(stack.isEmpty()){
        stack.push(x);
        stack.push(x);
    }else{
        int tmp = stack.peek();
        stack.push(x);
        if(tmp<x){
            stack.push(tmp);
        }else{
            stack.push(x);
        }
    }
}

public void pop() {
    stack.pop();
    stack.pop();
}

public int top() {
    return stack.get(stack.size()-2);
}

public int getMin() {
    return stack.peek();
}
}

//[搬运]英文leetcode高票解法，使用链表实现。

class MinStack {
    private Node head;
    
    public void push(int x) {
        if(head == null) 
            head = new Node(x, x);
        else 
            head = new Node(x, Math.min(x, head.min), head);
    }

    public void pop() {
        head = head.next;
    }

    public int top() {
        return head.val;
    }

    public int getMin() {
        return head.min;
    }
    
    private class Node {
        int val;
        int min;
        Node next;
        
        private Node(int val, int min) {
            this(val, min, null);
        }
        
        private Node(int val, int min, Node next) {
            this.val = val;
            this.min = min;
            this.next = next;
        }
    }
}
