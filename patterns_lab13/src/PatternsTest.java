
import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.List;

public class PatternsTest {

    private static final String textFileName = "textSample.txt";
    private static final String patternFileName = "patternSample.txt";

    public static void main(String[] args) throws IOException {

        List<Integer> offsets;

        offsets = naiveStringMatcher(getText(textFileName), getText(patternFileName));
        System.out.println(offsets);

    }

    public static List<Integer> naiveStringMatcher(String text, String pattern) {
        int n = text.length();
        int m = pattern.length();

        List<Integer> offsets = new ArrayList();

        char[] textChars = text.toCharArray();
        char[] patternChars = pattern.toCharArray();

        for (int offset = 0; offset < n - m; offset++) {
            int i = 0;
            while (i < m && textChars[offset + i] == patternChars[i] ) {
                i++;
            }

            if (i == m) {
                // pattern are true
                offsets.add(offset); // extend result
            }
        }

        return offsets;
    }

    private static String getText(String fileName) throws IOException {
        List<String> lines;
        lines = readStrings(fileName);
        String pattern = "";

        for (String line : lines) {
            pattern += line;
        }

        return pattern;
    }

    private static List<String> readStrings(String fileName) throws IOException {
        Path textFilePath = Paths.get(PatternsTest.class.getResource(fileName).getPath());
        return Files.readAllLines(textFilePath, StandardCharsets.UTF_8);
    }

}
