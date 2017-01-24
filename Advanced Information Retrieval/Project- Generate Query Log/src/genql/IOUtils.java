package genql;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author Amirhossein Aleyasen <aleyase2@illinois.edu>
 * created on Jun 23, 2016, 12:01:02 AM
 */
public class IOUtils {

    public static String SEPERATOR = "\t";
    public static String NEWLINE = "\n";

    public static void writeDataIntoFile(String content, String filepath) {
        writeDataIntoFile(content, filepath, true);
    }

    public static void writeDataIntoFile(String content, String filepath, boolean append) {
        FileWriter fw = null;
        try {
            File file = new File(filepath);
//            System.out.println("writeDataIntoFile filepath=" + file.getAbsolutePath());
            fw = new FileWriter(file, append);
            BufferedWriter bw = new BufferedWriter(fw);
            bw.write(content);
            bw.close();
            fw.close();
        } catch (IOException ex) {
            Logger.getLogger(IOUtils.class.getName()).log(Level.SEVERE, null, ex);
        } finally {
            try {
                fw.close();
            } catch (IOException ex) {
                Logger.getLogger(IOUtils.class.getName()).log(Level.SEVERE, null, ex);
            }
        }

    }

    public static List<String> readFileLineByLine(String filepath, boolean hasHeader) {
        return readFileLineByLine(filepath, null, hasHeader);
    }

    public static List<String> readFileLineByLine(String filepath, Integer limit, boolean hasHeader) {
        int count = 0;
        int max;
        if (limit == null) {
            max = Integer.MAX_VALUE;
        } else {
            max = limit;
        }
        List<String> lines = new ArrayList<>();
        try {
            BufferedReader br = new BufferedReader(new FileReader(filepath));
            String line = null;
            //ignore fist line
            if (hasHeader) {
                line = br.readLine();
            }
            line = br.readLine();
            count++;
            while (line != null) {
                lines.add(line);
                line = br.readLine();
                count++;
                if (count > max) {
                    break;
                }
            }
            br.close();
            return lines;
        } catch (IOException ex) {
            Logger.getLogger(IOUtils.class.getName()).log(Level.SEVERE, null, ex);
        }
        return null;
    }

}
