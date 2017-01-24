
package genql;

public class WordPopularity implements Comparable {
    private String word;
    private int popularity;
    private String fileName;

    public WordPopularity(String word, int popularity) {

        this.popularity = popularity;
        this.word = word;
    }

    public String getWord() {
        return word;
    }

    public int getPopularity() {
        return popularity;
    }

    @Override
    public int compareTo(Object o) {
        if(o instanceof WordPopularity) {
            return Integer.compare(popularity, ((WordPopularity) o).getPopularity());
        }
        return 0;
    }
}
