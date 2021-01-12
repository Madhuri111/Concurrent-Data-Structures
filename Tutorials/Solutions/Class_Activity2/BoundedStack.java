public class BoundedStack<T> {
	ReentrantLock pushLock, popLock;
	Condition notEmptyCondition, notFullCondition;
	AtomicInteger size;
	int capacity;
    class Node<T> {
        Node<T> next;
        T value;

        public Node(T value, Node<T> next) {
                this.next = next;
                this.value = value;
        }
    }
	public BoundedStack(int _capacity) {
		capacity = _capacity;
		head = new Node(null);
		size = new AtomicInteger(0);
		pushLock = new ReentrantLock();
		notFullCondition = pushLock.newCondition();
		popLock = new ReentrantLock();
		notEmptyCondition = popLock.newCondition();
	}
	public void enq(T x) {
		boolean mustWakeDequeuers = false;
		pushLock.lock();
		try {
        public void push(T value) {
                boolean sucessful = false;
                while (!sucessful) {
                        Node<T> oldTop = top.get();
                        Node<T> newTop = new Node<T>(value, oldTop);
                        sucessful = top.compareAndSet(oldTop, newTop);
                };
        }

		} finally {
			pushLock.unlock();
		}
	}
	public T deq() {
		T result;
		boolean mustWakeEnqueuers = true;
		popLock.lock();
		try {
			       public T pop() {
                boolean sucessful = false;
                Node<T> newTop = null;
                Node<T> oldTop = null;
                while (!sucessful) {
                        oldTop = top.get();
                        newTop = oldTop.next;
                        sucessful = top.compareAndSet(oldTop, newTop);
                }
                return oldTop.value;
        }
		} finally {
			popLock.unlock();
		}
		return result;
	}
}
