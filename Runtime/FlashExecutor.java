import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.nio.charset.Charset;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.List;
import java.util.Scanner;
import java.util.Stack;


/**
 * SER 502 Project 2 Group 31.
 * 
 * Flash Programming Language
 * 
 * Runtime Flash Executor
 * 
 */
public class FlashExecutor {
	public static void main(String argv[]) {

		try {
			executeFlClass(argv);
		} catch (FileNotFoundException e) {
			System.err.println(e.getLocalizedMessage());
		} catch (IOException e) {
			System.err.println(e.getLocalizedMessage());
		}
	}

	private static void executeFlClass(String[] argv) throws IOException {

		if (argv.length < 1) {
			System.err.println("Arguments must contain one or more .fl.class files");
			System.exit(1);
		}
		if (!argv[0].contains(".fl.class")) {
			System.err
					.println("Please enter a valid intermediate file. Received "
							+ argv[0]);
			System.exit(1);
		}
		FLConstants cmd = null;

		Stack<Object> valueStack = new Stack<Object>();
		Stack<Object> returnStack = new Stack<Object>();
		HashMap<String, Object> vList = new HashMap<String, Object>();
		HashMap<String, Function> functions = new HashMap<String, Function>();
		InputStream is = new FileInputStream(argv[0]);
		BufferedReader br = new BufferedReader(new InputStreamReader(is,
				Charset.forName("UTF-8")));

		ArrayList<String> fileLines = new ArrayList<String>();
		getFileCount(br, fileLines);
		String lineToScan = "";
		Scanner scan = null;
		int skipto = 0;
		int functionRefNumber = 0;
		boolean skip = false;
		String strVal = "";
		boolean skipForFunction = false;
		ArrayList<String> linesOfCode = new ArrayList<String>();
		String functionName = "";
		ArrayList<String> params = new ArrayList<String>();
		StringBuilder output = new StringBuilder();
		output.append("----------------------------------------------------------------------------\n");
		output.append("Output of " + argv[0] + "\n");
		for (int num = 0; num < fileLines.size(); num++) {
			if (skip) {
				num = skipto;
			}
			lineToScan = fileLines.get(num);
			if (lineToScan.equals("end_function")) {
				skipForFunction = false;
			}
			if (skipForFunction)
				linesOfCode.add(lineToScan);
			scan = new Scanner(lineToScan);
			skip = false;
			while (!skip && !skipForFunction) {
				boolean boolVal = false;
				boolean anInt = false;
				boolean aDouble = false;
				boolean aVariable = false;
				boolean aBool = false;
				boolean aString = false;
				Integer intVal = 0;
				Double doubleVal = 0.0;
				String variable = "";
				if (scan.hasNext()) {
					if (scan.hasNextInt()) {
						intVal = scan.nextInt();
						anInt = true;
					} else if (scan.hasNextDouble()) {
						doubleVal = scan.nextDouble();
						aDouble = true;
					} else {
						String str = scan.next();
						if (FLConstants.contains(str)) {
							cmd = FLConstants.valueOf(str.toUpperCase());
						} else if (str.startsWith("\"")) {
							strVal = str;
							aString = true;
						} else if (str.endsWith("\"")) {
							strVal = strVal + " " + str;
							aString = true;
						} else if (str.endsWith("bool")) {
							str = str.substring(0, str.indexOf("b"));
							aBool = true;
							boolVal = str.equals("1");
						} else {
							variable = str;
							aVariable = true;
						}
					}
					switch (cmd) {
					case PUSH:
						if (anInt) {
							valueStack.push(intVal);
						}
						if (aDouble) {
							valueStack.push(doubleVal);
						}
						if (aVariable) {
							if (!vList.containsKey(variable)) {
								vList.put(variable, 0.0);
							}
							valueStack.push(variable);
						}
						if (aString) {
							valueStack.push(strVal);
						}
						if (aBool) {
							valueStack.push(boolVal);
						}
						break;

					case ADD:
						String n1 = valueStack.pop().toString();
						String n2 = valueStack.pop().toString();
						String o1 = n1;
						String o2 = n2;
						if (stackElementIsAVariable(n1)) {
							o1 = vList.get(n1).toString();
						}
						if (stackElementIsAVariable(n2)) {
							o2 = vList.get(n2).toString();
						}
						if (!o1.contains("\"") && !(o2.contains("\"")) && !o1.matches("\\D+") && !o2.matches("\\D+")) {
							Double d1 = Double.valueOf(o1);
							Double d2 = Double.valueOf(o2);
							valueStack.push(d2 + d1);
						} else {
							valueStack.push("\""+o2.replaceAll("\"", "").concat(o1.replaceAll("\"", ""))+"\"");
						}
						break;
					case ASSIGN:
						n1 = valueStack.pop().toString();
						n2 = valueStack.pop().toString();
						o1 = n1;
						if (stackElementIsAVariable(n1)) {
							o1 = vList.get(n1).toString();
						}
						vList.put(n2, o1);

						break;
					case CALL_FUNCTION:
						functionName = scan.next();
						HashMap<String,Object> tmpList = new HashMap<String, Object>();
						if (scan.hasNext()) {
							params = new ArrayList<String>(Arrays.asList(scan
									.next().split(",")));
						}
						for(String s:params){
							tmpList.put(s, vList.get(s));
						}
						returnStack.push(tmpList);
						returnStack.push(num);
						num = functionRefNumber;
						assignParamValues(functions.get(functionName).params, params, vList, tmpList);
						break;
					case CONDITION_FALSE_JUMP_TO:
						skipto = scan.nextInt();
						if (!(Boolean) valueStack.pop()) {
							skip = true;
						} else {
							skipto = num;
						}
						break;
					case CONDITION_TRUE_JUMP_TO:
						skipto = scan.nextInt();
						if ((Boolean) valueStack.pop()) {
							skip = true;
						} else {
							skipto = num;
						}
						break;
					case DIVIDE:
						n1 = valueStack.pop().toString();
						n2 = valueStack.pop().toString();
						o1 = n1;
						o2 = n2;
						if (stackElementIsAVariable(n1)) {
							o1 = vList.get(n1).toString();
						}
						if (stackElementIsAVariable(n2)) {
							o2 = vList.get(n2).toString();
						}
						if (!o1.contains("\"") || !(o2.contains("\""))) {
							Double d1 = Double.valueOf(o1);
							Double d2 = Double.valueOf(o2);
							valueStack.push(d2 / d1);
						}
						break;
					case END:
						output.append("End of program\n");
						System.out.println(output.toString());
						break;
					case END_FUNCTION:
						
						if(!returnStack.isEmpty()){
							num = (Integer)returnStack.pop();
							//num = returnLineNumber;
						}
						else{
						Function fun = new Function(functionName, params,
						
								linesOfCode);
						functions.put(functionName, fun);
						}
						skipForFunction = false;
						break;
					case EQUAL:
						n1 = valueStack.pop().toString();
						n2 = valueStack.pop().toString();
						o1 = n1;
						o2 = n2;
						if (stackElementIsAVariable(n1)) {
							o1 = vList.get(n1).toString();
						}
						if (stackElementIsAVariable(n2)) {
							o2 = vList.get(n2).toString();
						}
						Double d1 = Double.valueOf(o1);
						Double d2 = Double.valueOf(o2);
						valueStack.push(d1.doubleValue() == d2.doubleValue());
						break;
					case FUNCTION:
						functionName = scan.next();
						if (scan.hasNext()) {
							params = new ArrayList<String>(Arrays.asList(scan
									.next().split(",")));
						}
						skipForFunction = true;
						functionRefNumber = num;
						break;
					case GREATER:
						n1 = valueStack.pop().toString();
						n2 = valueStack.pop().toString();
						o1 = n1;
						o2 = n2;
						if (stackElementIsAVariable(n1)) {
							o1 = vList.get(n1).toString();
						}
						if (stackElementIsAVariable(n2)) {
							o2 = vList.get(n2).toString();
						}
						d1 = Double.valueOf(o1);
						d2 = Double.valueOf(o2);
						valueStack.push(d2 > d1);
						break;
					case GREATER_THAN_EQUAL:
						n1 = valueStack.pop().toString();
						n2 = valueStack.pop().toString();
						o1 = n1;
						o2 = n2;
						if (stackElementIsAVariable(n1)) {
							o1 = vList.get(n1).toString();
						}
						if (stackElementIsAVariable(n2)) {
							o2 = vList.get(n2).toString();
						}
						d1 = Double.valueOf(o1);
						d2 = Double.valueOf(o2);
						valueStack.push(d2 >= d1);
						break;
					case LESSER:
						n1 = valueStack.pop().toString();
						n2 = valueStack.pop().toString();
						o1 = n1;
						o2 = n2;
						if (stackElementIsAVariable(n1)) {
							o1 = vList.get(n1).toString();
						}
						if (stackElementIsAVariable(n2)) {
							o2 = vList.get(n2).toString();
						}
						d1 = Double.valueOf(o1);
						d2 = Double.valueOf(o2);
						valueStack.push(d2 < d1);
						break;
					case LESSER_THAN_EQUAL:
						n1 = valueStack.pop().toString();
						n2 = valueStack.pop().toString();
						o1 = n1;
						o2 = n2;
						if (stackElementIsAVariable(n1)) {
							o1 = vList.get(n1).toString();
						}
						if (stackElementIsAVariable(n2)) {
							o2 = vList.get(n2).toString();
						}
						d1 = Double.valueOf(o1);
						d2 = Double.valueOf(o2);
						valueStack.push(d2 <= d1);
						break;
					case MODULUS:
						n1 = valueStack.pop().toString();
						n2 = valueStack.pop().toString();
						o1 = n1;
						o2 = n2;
						if (stackElementIsAVariable(n1)) {
							o1 = vList.get(n1).toString();
						}
						if (stackElementIsAVariable(n2)) {
							o2 = vList.get(n2).toString();
						}
						if (!o1.matches("\\s+") && !o2.matches("\\s+")) {
							d1 = Double.valueOf(o1);
							d2 = Double.valueOf(o2);
							if (d1 == 0.0) {
								valueStack.push(0);
							} else {
								valueStack.push(d2 % d1);
							}
						}
						break;
					case MULTIPLY:
						n1 = valueStack.pop().toString();
						n2 = valueStack.pop().toString();
						o1 = n1;
						o2 = n2;
						if (stackElementIsAVariable(n1)) {
							o1 = vList.get(n1).toString();
						}
						if (stackElementIsAVariable(n2)) {
							o2 = vList.get(n2).toString();
						}
						if (!o1.contains("\"") || !(o2.contains("\""))) {
							d1 = Double.valueOf(o1);
							d2 = Double.valueOf(o2);
							valueStack.push(d2 * d1);
						}
						break;
					case NOT_EQUAL:
						n1 = valueStack.pop().toString();
						n2 = valueStack.pop().toString();
						o1 = n1;
						o2 = n2;
						if (stackElementIsAVariable(n1)) {
							o1 = vList.get(n1).toString();
						}
						if (stackElementIsAVariable(n2)) {
							o2 = vList.get(n2).toString();
						}
						d1 = Double.valueOf(o1);
						d2 = Double.valueOf(o2);
						valueStack.push(d1.doubleValue() != d2.doubleValue());
						break;
					case PRINT:
						if (!valueStack.empty()) {
							String result = valueStack.pop().toString();
							String op = "";
							if (stackElementIsAVariable(result)) {
								op = vList.get(result).toString();
							}
							output.append(result + " = " + op + "\n");
						}
						break;
					case QUIT:
						System.err.println("Quiting program with error:"
								+ valueStack.pop().toString());
						System.exit(1);
						break;
					case RETURN:
						HashMap<String, Object> tList = new HashMap<String, Object>();
						n1 = valueStack.pop().toString();
						o1 = n1;
						if (stackElementIsAVariable(n1)) {
							o1 = vList.get(n1).toString();
						}
						valueStack.push(o1);
						if(!returnStack.isEmpty()) {
							num = (Integer)returnStack.pop();
							tList = (HashMap<String, Object>) returnStack.pop();
							for(String s:tList.keySet()){
								vList.put(s, tList.get(s));
							}
						}
						break;
					case SUB:
						n1 = valueStack.pop().toString();
						n2 = valueStack.pop().toString();
						o1 = n1;
						o2 = n2;
						if (stackElementIsAVariable(n1)) {
							o1 = vList.get(n1).toString();
						}
						if (stackElementIsAVariable(n2)) {
							o2 = vList.get(n2).toString();
						}
						if (!o1.contains("\"") || !(o2.contains("\""))) {
							d1 = Double.valueOf(o1);
							d2 = Double.valueOf(o2);
							valueStack.push(d2 - d1);
						}
						break;
					case ARGS:
						int i = 0;
						Object val = 0;
						while (i < intVal) {
							boolean isNumber = false; // default is false until
														// valid input is
														// detected
							System.out.println();
							System.out.print("Enter value: ");
							BufferedReader br1 = new BufferedReader(
									new InputStreamReader(System.in));
							while (!isNumber) {
								try {
									String input = br1.readLine();
									if(input.matches("\\D+")){
										val = "\""+ input +"\"";
									}else{
										val = Double.parseDouble(input);
									}
									isNumber = true;
									output.append("With Argument:" + val + "\n");
								} catch (Exception e) {
									System.out.print("Please enter a valid value: ");
								}
							}
							vList.put("arg[" + i + "]", val);
							i = i + 1;
						}
						break;
					default:
						System.out.println("Something went wrong " + cmd);
						break;
					}
				} else {
					break;
				}
			}
			scan.close();
		}
	}

	/**
	 * Checks if the element on top of the value stack is a variable.
	 * 
	 * @param element
	 * @return
	 */
	private static boolean stackElementIsAVariable(String element) {
		return !element.matches("\\d+") && !element.contains(".")
				&& !element.contains("\"") && !element.matches("true|false");
	}

	private static int getFileCount(BufferedReader br, ArrayList<String> lines)
			throws IOException {
		String line = "";
		int count = 0;
		while ((line = br.readLine()) != null) {
			count++;
			lines.add(line);
		}
		return count;
	}
	
	private static void assignParamValues(List<String>funParams, List<String>params, HashMap<String, Object> vList, HashMap<String,Object> tmpList){
		for(int i =0 ;i<funParams.size();i++){
			vList.put(funParams.get(i), tmpList.get(params.get(i)));
		}
	}

}