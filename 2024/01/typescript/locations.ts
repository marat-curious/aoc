export class Locations {
  _left: Array<number> = [];
  _right: Array<number> = [];

  fill(locations: [number, number]) {
    const [left, right] = locations;
    this._left.push(left);
    this._right.push(right);
  }

  getDistance() {
    const sortFunc = (a: number, b: number) => a - b;
    this._left.sort(sortFunc);
    this._right.sort(sortFunc);
    return this._right
      .map((n, i) => Math.abs(n - this._left[i]))
      .reduce((acc, cur) => (acc += cur, acc), 0);
  }
}
