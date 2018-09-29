
import java.io.*;
import java.util.*;


class MatchGroup
{
    public TreeSet<Integer> plainIndices = new TreeSet<Integer>();
    public TreeSet<Integer> cipherIndices = new TreeSet<Integer>();
}


public class KeyInsight
{

    static long factorial(int n) {
        long answer = 1;
        while (n > 1) {
            answer *= n;
            n--;
        }
        return answer;
    }

    static List<MatchGroup> blockKeys(String plain, String cipher)
    {
        List<MatchGroup> result = new ArrayList<MatchGroup>();

        char[] pchars = plain.toCharArray();
        char[] cchars = cipher.toCharArray();
        Arrays.sort(pchars);
        Arrays.sort(cchars);
        if (!Arrays.equals(pchars, cchars))
            return result;

        int k = plain.length();
        pchars = plain.toCharArray();
        cchars = cipher.toCharArray();

        for (char c = 'a'; c <= 'z'; c++) {
            MatchGroup g = new MatchGroup();
            for (int i = 0; i < k; i++) {
                if (plain.charAt(i) == c)
                    g.plainIndices.add(i);
                if (cipher.charAt(i) == c)
                    g.cipherIndices.add(i);
            }
            if (g.plainIndices.size() > 0 && g.plainIndices.size() == g.cipherIndices.size())
                result.add(g);
        }

        return result;
    }

    static List<MatchGroup> mergeKeySets(List<MatchGroup> aset, List<MatchGroup> bset)
    {
        List<MatchGroup> result = new ArrayList<MatchGroup>();
        for (MatchGroup ga : aset) {
            for (MatchGroup gb : bset) {
                MatchGroup ng = new MatchGroup();
                ng.plainIndices.addAll(ga.plainIndices);
                ng.plainIndices.retainAll(gb.plainIndices);
                ng.cipherIndices.addAll(ga.cipherIndices);
                ng.cipherIndices.retainAll(gb.cipherIndices);
                if (ng.plainIndices.size() > 0 && ng.plainIndices.size() == ng.cipherIndices.size())
                    result.add(ng);
            }
        }
        return result;
    }

    static long solve(int k, String plain, String cipher)
    {
        MatchGroup allMatch = new MatchGroup();
        for (int i = 0; i < k; i++) {
            allMatch.plainIndices.add(i);
            allMatch.cipherIndices.add(i);
        }

        List<MatchGroup> goodKeys = new ArrayList<MatchGroup>();
        goodKeys.add(allMatch);

        for (int p = 0; p < plain.length(); p += k) {
            String plainBlock = plain.substring(p, p+k);
            String cipherBlock = cipher.substring(p, p+k);
            List<MatchGroup> bk = blockKeys(plainBlock, cipherBlock);
            goodKeys = mergeKeySets(goodKeys, bk);
        }

        if (goodKeys.isEmpty())
            return 0;

        long answer = 1;
        for (MatchGroup g : goodKeys) {
            int n = g.plainIndices.size();
            answer = answer * factorial(n);
        }

        return answer;
    }

    public static void main(String[] args)
    {
        try {
            BufferedReader ir = new BufferedReader(new InputStreamReader(System.in));
            String s = ir.readLine();
            while (s != null) {
                int k = Integer.parseInt(s);
                String plain = ir.readLine();
                String cipher = ir.readLine();
                assert (k >= 1);
                assert (plain.length() >= 1 && plain.length() <= 100);
                assert (plain.length() == cipher.length());
                assert (plain.length() % k == 0);
                for (int i = 0; i < plain.length(); i++) {
                    assert (plain.charAt(i) >=  'a' && plain.charAt(i) <= 'z');
                    assert (cipher.charAt(i) >=  'a' && cipher.charAt(i) <= 'z');
                }
                long answer = solve(k, plain, cipher);
                System.out.println(answer);
                s = ir.readLine();
            }
        } catch (IOException e) {
            e.printStackTrace();
            System.exit(1);
        }
    }

}
