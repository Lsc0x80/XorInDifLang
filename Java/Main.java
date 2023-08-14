package Java;

import java.util.Base64;

class Main {
    public static void main(String[] args) {
        String key = args[0];
        String text = args[1];
        Base64.Encoder encoder = Base64.getEncoder();
        Base64.Decoder decoder = Base64.getDecoder();

        System.out.println("key: "+key);
        System.out.println("text: "+text);
        //char[] textc = text.toCharArray();
        //char[] keyc = key.toCharArray();
        int k = 0;
        int kl = key.length()-1;
        byte[] cryptotext = new byte[text.length()];
        for (int i = 0; i < text.length(); i++){
            cryptotext[i] = (byte) (text.charAt(i) ^ key.charAt(k));
            if (k == kl) k = 0;
            else k++;
        }
        System.out.println(encoder.encodeToString(cryptotext));
    }
}