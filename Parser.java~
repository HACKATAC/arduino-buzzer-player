import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.util.ArrayList;
import java.util.List;

/**
 * Created by runix on 11/18/14.
 */
public class Parser {
    public static void main(String [] args) throws Exception
    {
          for(int i = 0; i < args.length; i++) {
              if(args[i].trim().equals("parse")) {
                  parse(args[++i]);
              }else if(args[i].trim().equals("parseName")) {
                  parseName(args[++i].trim());
              }
          }
    }

    private static void parseName(String name) throws Exception {
        int actual = 0;
        List<Integer> joined = new ArrayList<Integer>();
        System.out.println("Name "+name+" length "+name.length());
        for(int count = 0; count < name.length(); count ++) {
            if(count % 4 == 0 &&  count != 0) {
                joined.add(actual);
                actual = 0;
            }
            int actualChar = name.toCharArray()[count];
            actualChar = actualChar << (8*(count % 4));
            actual = actual | (actualChar);
        }
        joined.add(actual);
        for(Integer join : joined) {
            int value = join.intValue();
            System.out.print((char) ((value >> 0) & 0xFF) + "" + (char) ((value >> 8) & 0xFF) + "" + (char) ((value >> 16) & 0xFF) + "" + (char) ((value >> 24) & 0xFF) + "");
        }
        System.out.println(joined.toString().replace('[',' ').replace(']', ' '));
    }
    private static void parse(String file) throws Exception {
        File f = new File(file);
        BufferedReader reader = new BufferedReader(new FileReader(f));
        String line;
        int count = 0;
        while((line = reader.readLine()) != null) {
            if(!(line.contains("int") || line.isEmpty() || line.equals("\n") || line.contains("};"))) {
                String[] split = line.split(",");
                System.out.println("// tone: "+split[0] + " duration "+split[1]);
                int tone = Integer.parseInt(split[0].replace('\n', ' ').trim());
                int duration = Integer.parseInt(split[1].replace('\n', ' ').trim());
                int reduced = tone << 16;
                reduced = reduced | duration;
                System.out.println(reduced+",");
                count++;
            } else {
                System.out.println(line);
            }
        }
        System.out.println("\n\nNumber of numbers "+count+" memory used : "+count*4+" bytes");
    }
}
