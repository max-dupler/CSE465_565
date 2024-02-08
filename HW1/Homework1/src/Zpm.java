/**
 * Copyright 2024 Max Dupler
 * Portions of this code were adapted with assistance from the OpenAI GPT-3 model. All rights reserved.
 * Specific portions assisted by ChatGPT inlude:
 *      Comment generation
 *      Assistance with errors in the assignment and forLoop methods
 */

import java.io.FileReader;
import java.io.BufferedReader;
import java.io.IOException;
import java.util.HashMap;
import java.util.Map;


public class Zpm {

    private static Map<String, Object> variables = new HashMap<>();
    public static void main(String[] args) throws Exception {
        if (args.length < 1) {
            System.out.println("Usage: java Zpm <filename.zpm>");
            return;
        }

        String fileName = args[0];
        int lineNum = 0;

        try(BufferedReader reader = new BufferedReader(new FileReader(fileName))) {
            String line;
            while ((line = reader.readLine()) != null) {
                lineNum++;
                interpret(line.trim());
            }
        } catch (IOException e) {
            System.err.println("Runtime Error: Line " + lineNum);
        }
    }

    private static void interpret(String line) {
        if (line.isEmpty()) {
            return;
        }

        String[] parts = line.split("\\s+");

        if (parts.length < 3 || (!parts[parts.length - 1].equals(";")
            && !parts[parts.length - 1].equals("ENDFOR"))) {
            System.err.println("Syntax Error " + line);
            return;
        }

        switch(parts[0]) {
            case "PRINT":
                printVariables(parts[1]);
                break;
            case "FOR":
                forLoop(parts);
                break;
            default:
                assignment(parts);
        }
    }

    private static void assignment(String[] parts) {
        String variable = parts[0];
        String operation = parts[1];
        String value = parts[2];

        if (operation.equals("=")) {
            variables.put(variable, parseValue(value));
        } else {
            Object currentValue = variables.get(variable);
            if (currentValue == null) {
                System.err.println("Runtime error: " + variable + " not assigned");
                return;
            }
            switch (operation) {
                case "+=":
                    if (currentValue instanceof String && parseValue(value) instanceof String) {
                        variables.put(variable, (String) currentValue + (String) parseValue(value));
                    } else if (currentValue instanceof Integer && parseValue(value) instanceof Integer) {
                        variables.put(variable, (Integer) currentValue + (Integer) parseValue(value));
                    } else {
                        System.err.println("Runtime error: Invalid operation (+=)");
                    }
                    break;
                case "*=":
                    if (currentValue instanceof Integer && parseValue(value) instanceof Integer) {
                        variables.put(variable, (Integer) currentValue * (Integer) parseValue(value));
                    } else {
                        System.err.println("Runtime error: Invalid operation");
                    }
                    break;
                case "-=":
                    if (currentValue instanceof Integer && parseValue(value) instanceof Integer) {
                        variables.put(variable, (Integer) currentValue - (Integer) parseValue(value));
                    } else {
                        System.err.println("Runtime error: Invalid operation");
                    }
                    break;
                default:
                    System.err.println("Syntax error: " + parts[1]);
            }
        }
    }

    private static void forLoop(String[] parts) {
        int numLoops = Integer.parseInt(parts[1]);
        
        for (int i = 0; i < numLoops; i++) {
            StringBuilder statement = new StringBuilder();
    
            for (int j = 2; j < parts.length; j++) {
                if (parts[j].equals(";")) {
                    statement.append(" ;");
                    interpret(statement.toString().trim());
                    statement.setLength(0);
                } else if (parts[j].equals("ENDFOR")) {
                    break;
                } else {
                    statement.append(parts[j]).append(" ");
                }
            }
        }
        
        if (!parts[parts.length - 1].equals("ENDFOR")) {
            System.err.println("Syntax error: Missing ENDFOR");
        }
    }

    private static void printVariables(String variable) {
        Object value = variables.get(variable);
        if (value == null) {
            System.err.println("Runtime error: Variable " + variable + " not initialized");
        } else {
            System.out.println(variable + "=" + value);
        }
    }

    private static Object parseValue(String value) {
        try {
            if (isNumeric(value)) {
                return Integer.parseInt(value);
            } else {
                if (value.startsWith("\"") && value.endsWith("\"") && value.length() >= 2) {
                    return value.substring(1, value.length() - 1);
                } else {
                    return Integer.parseInt(variables.get(value).toString());
                }
            }
        } catch (NumberFormatException e) {
            return value;
        }
    }

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
