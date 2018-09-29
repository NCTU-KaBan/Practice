// @EXPECTED_RESULTS@: CORRECT

import java.io.*;
import java.util.*;


public class DigitalClock
{

    static class Time
    {
        int t;

        public Time(int t)
        {
            this.t = t;
        }

        public String toString()
        {
            return "" + (t / 600) + "" + ((t / 60) % 10) +
                   ":" + ((t / 10) % 6) + "" + (t % 10);
        }

        public int digit(int i)
        {
            switch (i) {
                case 0: return t / 600;
                case 1: return (t / 60) % 10;
                case 2: return (t / 10) % 6;
                case 3: return t % 10;
            }
            assert(false);
            return -1;
        }

        public Time later(int dt)
        {
            return new Time((t + dt) % (24 * 60));
        }
    }


    static class Pattern
    {
        int[] digits;

        public Pattern(String s)
        {
            assert(s.length() == 5);
            assert(s.charAt(2) == ':');
            digits = new int[4];
            digits[0] = Integer.parseInt(s.substring(0, 1));
            digits[1] = Integer.parseInt(s.substring(1, 2));
            digits[2] = Integer.parseInt(s.substring(3, 4));
            digits[3] = Integer.parseInt(s.substring(4, 5));
        }

        public String toString()
        {
            return "" + digits[0] + "" + digits[1] +
                  ":" + digits[2] + "" + digits[3];
        }

        public int digit(int i)
        {
            return digits[i];
        }
    }


    static class Digit
    {
        int goodSegments;
        int badSegments;

        public Digit()
        {
            goodSegments = 0;
            badSegments  = 0;
        }

        public void observe(int expected, int observed)
        {
            goodSegments |= digitToSegments(observed);
            badSegments  |= (digitToSegments(expected) ^ digitToSegments(observed));
        }

        public boolean possible()
        {
            return (goodSegments & badSegments) == 0;
        }

        private int digitToSegments(int digit)
        {
            switch (digit) {
                case 0: return 1+2+4+16+32+64;
                case 1: return 32+64;
                case 2: return 2+4+8+16+32;
                case 3: return 4+8+16+32+64;
                case 4: return 1+8+32+64;
                case 5: return 1+4+8+16+64;
                case 6: return 127-32;
                case 7: return 4+32+64;
                case 8: return 127;
                case 9: return 127-2;
            }
            assert(false);
            return -1;
        }

    }


    static class Clock
    {
        Digit[] digits;

        public Clock()
        {
            digits = new Digit[4];
            for (int i = 0; i < 4; i++)
                digits[i] = new Digit();
        }

        public void observe(Time expected, Pattern observed)
        {
            for (int i = 0; i < 4; i++)
                digits[i].observe(expected.digit(i), observed.digit(i));
        }

        public boolean possible()
        {
            for (int i = 0; i < 4; i++)
                if (!digits[i].possible())
                    return false;
            return true;
        }
    }


    public static void main(String[] args)
    {

        try {
            BufferedReader reader = new BufferedReader(
                new InputStreamReader(System.in));

            String s = reader.readLine();
            while (s != null) {

                String[] words = s.split(" ");

                int n = Integer.parseInt(words[0]);
                assert (n == words.length - 1);
                assert (n <= 50);

                List<Pattern> patterns = new ArrayList<Pattern>();
                for (int i = 0; i < n; i++)
                    patterns.add(new Pattern(words[i+1]));

                List<Time> answers = solve(patterns);
                if (answers.isEmpty()) {
                    System.out.println("none");
                } else {
                    StringBuffer sb = new StringBuffer();
                    sb.append(answers.get(0));
                    for (Time t: answers.subList(1, answers.size())) {
                        sb.append(" ");
                        sb.append(t);
                    }
                    System.out.println(sb);
                }

                s = reader.readLine();
            }

        } catch (IOException e) {
            e.printStackTrace();
            System.exit(1);
        }

    }


    static List<Time> solve(List<Pattern> patterns)
    {
        List<Time> answers = new ArrayList<Time>();

        for (int k = 0; k < 24 * 60; k++) {
            Time startTime = new Time(k);
            Clock clock = new Clock();

            for (int i = 0; i < patterns.size(); i++)
                clock.observe(startTime.later(i), patterns.get(i));

            if (clock.possible())
                answers.add(startTime);
        }

        return answers;
    }

}
