# User Guide – Linux Driver Evaluation System

This guide explains how to use the evaluation pipeline to assess Linux driver `.c` files for quality, security, and compilation validity.

---

## Getting Started

1. Open the Colab notebook or local environment
2. Upload your `.c` file (e.g., `my_driver.c`)
3. Ensure required files are in place:
   - `checkpatch.pl` script
   - Driver file uploaded
   - Colab runtime active (T4 GPU or CPU)

---

## Step-by-Step Execution

### 1. Compilation

```python
compile_result = compile_driver("my_driver.c")
````

*  If it compiles → `"success": true`
*  If it fails → `"success": false` and score penalty applied

---

### 2. Style Compliance

```python
style_result = check_style("my_driver.c")
```

* Uses `checkpatch.pl` to calculate style score
* Outputs `style_score` ∈ \[0.0, 1.0]

---

### 3. Security Heuristics

```python
security_result = run_security_checks("my_driver.c")
```

* Analyzes code for:

  * Buffer safety
  * Race condition signs
  * Input validation

---

### 4. Final Scoring

```python
final_score = calculate_score(compile_result, style_result, security_result)
```

* Combines all modules using weighted rubric
* Outputs a float score (0.0–100.0)

---

### 5. Save Output (Optional)

```python
with open("evaluation_result.json", "w") as f:
    json.dump({
        "compilation": compile_result,
        "code_quality": style_result,
        "security": security_result,
        "overall_score": final_score
    }, f, indent=4)
```

---

## Example Output

```json
{
  "compilation": {"success": false},
  "code_quality": {"style_score": 1.0},
  "security": {
    "buffer_safety": 1.0,
    "race_conditions": 0.5,
    "input_validation": 0.4
  },
  "overall_score": 35.83
}
```

---

## Tips

* Use real Linux drivers or LLM-generated `.c` files
* Bonus: Try `test_driver_sim.c` to test runtime behavior
* Compilation may fail if Linux kernel headers are missing — this is expected in Colab

---

## Author

Divyansh Gautam
ML Internship Assignment – Driver Evaluation System

```
