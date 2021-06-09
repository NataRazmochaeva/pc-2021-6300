import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.atomic.AtomicMarkableReference;


/**
 * Lock-Free set.
 * 
 * @param <T> kays type
 */
public class LockFreeSet<T extends Comparable<T>> {

    private class StackNode<T> {
        AtomicMarkableReference<StackNode<T>> next;
        T value;

        public StackNode(T value, StackNode<T> next) {
            this.next = new AtomicMarkableReference<StackNode<T>>(next, false);
            this.value = value;
        }
    }

    // Defining the stack nodes as Atomic Reference
    StackNode<T> headNode = new StackNode<T>(null, null);
    private AtomicMarkableReference<StackNode<T>> head = head = new AtomicMarkableReference<StackNode<T>>(headNode,
            false);

   

    /**
     * Adding kay to array
     *
     * Algorithm must be developed at least in lock-free style
     *
     * @param value -- value of key
     * @return false -- if value is already exists in array, true -- if item with
     *         value was successfully added
     */
    boolean add(T value) {
        if (value == null) {
            return false;
        }
        boolean sucessful = false;
        while (!sucessful) {
            boolean found = false;
            for (StackNode<T> node = head.getReference(); node != null
                    && !node.next.isMarked(); node = node.next.getReference()) {
                if (node.value.equals(head.getReference().value) && !node.next.isMarked()) {
                    found = true;
                    StackNode<T> nextNode = node.next.getReference();
                    StackNode<T> newNode = new StackNode<T>(value, nextNode);
                    sucessful = node.next.compareAndSet(nextNode, newNode, false, false);
                    break;
                }
            }
            if (!found) {
                return false;
            }
        }
        return true;
    }

    /**
     * Delete key from array
     *
     * Algorithm must be developed at least in lock-free style
     *
     * @param value -- value of key
     * @return false -- if the key was not found, true -- if the key was
     *         successfully deleted
     */
    boolean remove(T value) {
        if (value == null) {
            return false;
        }
        boolean sucessful = false;
        while (!sucessful) {
            boolean found = false;
            for (StackNode<T> node = head.getReference(),
                    nextNode = node.next.getReference(); nextNode != null; node = nextNode, nextNode = nextNode.next
                            .getReference()) {
                if (!nextNode.next.isMarked() && nextNode.value.equals(value)) {
                    found = true;
                    while (!node.next.attemptMark(node.next.getReference(), true)) {
                    }
                    StackNode<T> rightNode = nextNode;
                    do {
                        rightNode = rightNode.next.getReference();
                    } while (rightNode != null && rightNode.next.isMarked());
                    sucessful = node.next.compareAndSet(node, rightNode, false, false);
                    break;
                }
            }
            if (!found) {
                return false;
            }
        }
        return true;
    }

    /**
     * Checking if the key is in array
     *
     * The algorithm should be at least wait-free for types of finite dimension and
     * lock-free for the rest.
     *
     * @param value -- value of the key
     * @return true -- if the key is in array, otherwise - false
     */
    boolean contains(T value) {
        boolean found = false;
        for (StackNode<T> node = head.getReference(),
                nextNode = node.next.getReference(); nextNode != null; node = nextNode, nextNode = nextNode.next
                        .getReference()) {
            if (!nextNode.next.isMarked() && nextNode.value.equals(value)) {
                found = true;
            }

        }
        return found;
    }

    /**
     * Checking if the array is empty
     *
     * Algorithm must be developed at least in lock-free style
     *
     * @return true -- if the array is empty, otherwise - false
     */
    boolean isEmpty() {
        return createList().isEmpty();
    }

    private List<StackNode<T>> createList() {
        ArrayList<StackNode<T>> list = new ArrayList<>();
        for (StackNode<T> node = head.getReference(); node != null; node = node.next.getReference()) {
            if (node != head.getReference() && !node.next.isMarked()) {
                list.add(node);
            }
        }
        return list;
    }

    /**
     * Returns lock-free iterator for array
     *
     * @return new entity of iterator for array
     */
    java.util.Iterator<T> iterator() {
        while (true) {
            List<StackNode<T>> snapshot1 = createList();
            List<StackNode<T>> snapshot2 = createList();
            if (snapshot1.size() == snapshot2.size() && snapshot1.containsAll(snapshot2)) {
                return snapshot1.stream().map(node -> node.value).iterator();
            }
        }
    }
}

