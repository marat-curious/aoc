const MAX_DIFF = 3;
const MIN_DIFF = 1;

export class Solution {
  _checks: Array<boolean> = [];

  check(report: Array<number>) {
    if (report.length < 2) {
      this._checks.push(false);
      return;
    }

    let sign = 0;

    for (let i = 1; i < report.length; i++) {
      const diff = report[i] - report[i - 1];

      if (!sign) {
        sign = diff / Math.abs(diff);
      }

      if ((sign < 0 && diff > 0) || (sign > 0 && diff < 0) || Math.abs(diff) > MAX_DIFF || Math.abs(diff) < MIN_DIFF) {
        this._checks.push(false);
        return;
      }
    }

    this._checks.push(true);
  }

  answer() {
    console.log('Part 1:', this._checks.filter(Boolean).length);
  }
}
