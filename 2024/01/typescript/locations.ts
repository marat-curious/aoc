export class Locations {
  _left: Array<number> = [];
  _right: Array<number> = [];
  _appears: Record<string, number> = {};

  fill(locations: [number, number]) {
    const [left, right] = locations;
    this._left.push(left);
    this._right.push(right);
    this._appears[right] = typeof this._appears[right] !== 'undefined' ? ++this._appears[right] : 1;
  }

  getDistance() {
    const sortFunc = (a: number, b: number) => a - b;
    this._left.sort(sortFunc);
    this._right.sort(sortFunc);
    return this._right
      .map((n, i) => Math.abs(n - this._left[i]))
      .reduce((acc, cur) => (acc += cur, acc), 0);
  }

  getSimilarity() {
    return this._left.reduce((acc, cur) => (acc += cur * (this._appears[cur] || 0), acc), 0);
  }
}
