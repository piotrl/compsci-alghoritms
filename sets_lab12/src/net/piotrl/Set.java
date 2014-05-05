package net.piotrl;

public class Set {
    private int key;
    private int rank;
    private Set parent;

    private Set(int k) {
        this.key = k;
        this.rank = 0;
        this.parent = this;
    }

    public static Set make(int k) {
        return new Set(k);
    }

    public static Set find(Set x) {
        if (x != x.parent) {
            x.parent = find(x.parent);
        }

        return x.parent;
    }

    public void union(Set y) {
        link(find(this), find(y));   // link only represents
    }

    private void link(Set x, Set y) {
        if (x.rank > y.rank) {
            y.parent = x;
        }
        else {
            x.parent = y;
            if (x.rank == y.rank) {
                y.rank++;
            }
        }
    }

    @Override
    public String toString() {
        return "key: " + this.key + ", rank: " + this.rank + ", parent: " + this.parent.key + "\n";
    }
}
