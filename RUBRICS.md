# Rubrics – Evaluation Scoring Criteria

This document defines the rubric used to evaluate Linux device driver `.c` files submitted for analysis. It includes weighted scoring logic, metric design, and penalty considerations.

---

## Scoring Breakdown (Out of 100)

| Metric           | Weight (%) | Description |
|------------------|------------|-------------|
| Compilation      | 40%        | Can the code compile with `gcc`? |
| Code Quality     | 20%        | Style compliance score via `checkpatch.pl` |
| Security Heuristics | 25%     | Heuristic checks for risky patterns |
| Performance/Runtime (Bonus) | 10%*       | Simulated runtime test |
| Advanced/LLM Bonus (Unscored) | 5%*        | Documented but not scored numerically |

> Total: 85% is core logic, 15% is bonus/documented

---

## Scoring Function Logic

### Compilation
- `success: true` → Full 40 points
- `false` → 0 points
- Warnings don't reduce score, but noted

### Style Score
- `style_score` ∈ [0.0, 1.0]
- Multiplied by 20 → e.g. score = 0.75 × 20 = 15

### Security
- 3 sub-scores: `buffer_safety`, `race_conditions`, `input_validation`
- Each ∈ [0.0, 1.0]
- Averaged → multiplied by 25

### Bonus Runtime Test
- Runtime simulation (`test_driver_sim.c`) shows buffer correctness
- Not directly scored, but included in submission

---

## Sample Breakdown

| Metric        | Score   |
|---------------|---------|
| Compilation   | 0       |
| Style         | 1.0     |
| Security Avg  | 0.63    |
| Final Score   | **35.83** |

---

## Penalty Triggers

- Compilation fail → full 40% lost
- Style or security violations → proportional deductions
- Insecure patterns (no buffer safety or validation) → lower score

---

## Why These Rubrics?

Linux kernel code requires:
- High stability
- Clean style
- Defensive programming

These rubrics mimic real-world kernel review expectations.

---

## Author

Divyansh Gautam  
ML Internship Assignment – Kernel Driver Evaluation System
```
