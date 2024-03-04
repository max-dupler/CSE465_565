/**
 * This class represents a Zpm interpreter.
 * 
 * Portions of this code were adapted with assistance from the OpenAI GPT-3 model. All rights reserved.
 * Specific portions assisted by ChatGPT include:
 *   - Comment generation
 *   - Assistance with errors in the assignment and forLoop methods
 */
import java.io.FileReader;
import java.io.BufferedReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class Zpm {

    // Map to store variables and their values
    private static Map<String, Object> variables = new HashMap<>();

    /**
     * Main method to run the Zpm interpreter.
     * 
     * @param args Command-line arguments containing the filename to interpret.
     */
    public static void main(String[] args) throws Exception {
        if (args.length < 1) {
            System.out.println("Usage: java Zpm <filename.zpm>");
            return;
        }

        String fileName = args[0];
        int lineNum = 0;

        try(BufferedReader reader = new BufferedReader(new FileReader(fileName))) {
            String line;
            // Read each line from the file and interpret it
            while ((line = reader.readLine()) != null) {
                lineNum++;
                interpret(line.trim(), lineNum);
            }
        } catch (IOException | RuntimeException e) {
            // Handle IOException and RuntimeException
            if (e instanceof IOException) {
                System.err.println("Syntax Error: Line " + lineNum);
            } else {
                System.err.println("Runtime Error: Line " + lineNum);
            }
            return;
        }
    }

    /**
     * Tokenizes a string into individual tokens based on whitespace,
     * preserving substrings within quotes as single tokens.
     *
     * @param line The string to be tokenized.
     * @return An array of tokens extracted from the input string.
     */
    private static String[] tokenize(String line) {
        List<String> tokens = new ArrayList<>();
        StringBuilder currentToken = new StringBuilder();
        boolean withinQuotes = false;
    
        for (char c : line.toCharArray()) {
            if (c == '"') {
                withinQuotes = !withinQuotes;
            }
    
            if (Character.isWhitespace(c) && !withinQuotes) {
                if (currentToken.length() > 0) {
                    tokens.add(currentToken.toString());
                    currentToken.setLength(0);
                }
            } else {
                currentToken.append(c);
            }
        }
    
        if (currentToken.length() > 0) {
            tokens.add(currentToken.toString());
        }
    
        return tokens.toArray(new String[0]);
    }

    /**
     * Interpret a line of Zpm code.
     * 
     * @param line The line of Zpm code to interpret.
     * @param lineNum The line number being interpreted.
     */
    private static void interpret(String line, int lineNum) throws Exception {
        if (line.isEmpty()) {
            return;
        }

        String[] parts = tokenize(line);
        // Check for syntax errors
        if (parts.length < 3 || (!parts[parts.length - 1].equals(";") 
            && !parts[parts.length - 1].equals("ENDFOR"))) {
            throw new IOException();
        }
        switch(parts[0]) {
            case "PRINT":
                printVariables(parts[1], lineNum);
                break;
            case "FOR":
                forLoop(parts, lineNum);
                break;
            default:
                assignment(parts, lineNum);
        }
    }

    /**
     * Perform an assignment operation.
     * 
     * @param parts The parts of the assignment operation.
     * @param lineNum The line number being interpreted.
     */
    private static void assignment(String[] parts, int lineNum) throws Exception {
        String variable = parts[0];
        String operation = parts[1];
        String value = parts[2];
    
        if (operation.equals("=")) {
            variables.put(variable, parseValue(value));
        } else {
            Object currentValue = variables.get(variable);
            if (currentValue == null) {
                throw new RuntimeException();
            }
            switch (operation) {
                case "+=":
                    if (currentValue instanceof String || parseValue(value) instanceof String) {
                        variables.put(variable, String.valueOf(currentValue) + String.valueOf(parseValue(value)));
                    } else if (currentValue instanceof Integer && parseValue(value) instanceof Integer) {
                        variables.put(variable, (Integer) currentValue + (Integer) parseValue(value));
                    } else {
                        throw new RuntimeException();
                    }
                    break;
                case "-=":
                    if (currentValue instanceof Integer && parseValue(value) instanceof Integer) {
                        variables.put(variable, (Integer) currentValue - (Integer) parseValue(value));
                    } else {
                        throw new RuntimeException();
                    }
                    break;
                case "*=":
                    Object parsedValue = parseValue(value);
                    if (currentValue instanceof Integer && parsedValue instanceof Integer) {
                        variables.put(variable, (Integer) currentValue * (Integer) parsedValue);
                    } else {
                        throw new RuntimeException();
                    }
                    break;
                default:
                    throw new IOException();
            }
        }
    }
    
    

    /**
     * Perform a for loop operation.
     * 
     * @param parts The parts of the for loop operation.
     * @param lineNum The line number being interpreted.
     */
    private static void forLoop(String[] parts, int lineNum) throws Exception {
        int numLoops = Integer.parseInt(parts[1]);
        
        for (int i = 0; i < numLoops; i++) {
            StringBuilder statement = new StringBuilder();
    
            for (int j = 2; j < parts.length; j++) {
                if (parts[j].equals(";")) {
                    statement.append(" ;");
                    interpret(statement.toString().trim(), lineNum);
                    statement.setLength(0);
                } else if (parts[j].equals("ENDFOR")) {
                    break;
                } else {
                    statement.append(parts[j]).append(" ");
                }
            }
        }
        
        if (!parts[parts.length - 1].equals("ENDFOR")) {
            throw new IOException();
        }
    }

    /**
     * Print the value of a variable.
     * 
     * @param variable The name of the variable to print.
     * @param lineNum The line number being interpreted.
     */
    private static void printVariables(String variable, int lineNum) throws Exception {
        Object value = variables.get(variable);
        if (value == null) {
            throw new RuntimeException();
        } else {
            System.out.println(variable + "=" + value);
        }
    }

    /**
     * Parse the value of a variable.
     * 
     * @param value The value to parse.
     * @return The parsed value.
     */
    private static Object parseValue(String value) {
        try {
            if (isNumeric(value) || value.charAt(0) == '-') {
                return Integer.parseInt(value);
            } else {
                if (value.startsWith("\"") && value.endsWith("\"") && value.length() >= 2) {
                    return value.substring(1, value.length() - 1);
                } else {
                    if (variables.containsKey(value)) {
                        Object varValue = variables.get(value);
                        if (varValue instanceof Integer) {
                            return varValue;
                        } else if (varValue instanceof String) {
                            return varValue;
                        }
                    }
                }
            }
        } catch (NumberFormatException e) {
            return value;
        }
        return value; // return as is if not handled otherwise
    }
    

    /**
     * Check if a string is numeric.
     * 
     * @param str The string to check.
     * @return True if the string is numeric, false otherwise.
     */
    private static boolean isNumeric(String str) {
        // Check if each character in the string is a digit
        for (char c : str.toCharArray()) {
            if (!Character.isDigit(c)) {
                return false; // If any character is not a digit, return false
            }
        }
        return true; // All characters are digits, return true
    }
}
