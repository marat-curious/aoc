const inputFilename = "input";
const rawData = await Deno.readTextFile(inputFilename);
const data: string[][] = rawData
  .split(/\r?\n/)
  .map((d) => d.split(' '));

const getPosition = (d: string[][]): number[] => {
  let result = [0, 0];
  d.forEach(([direction, steps]) => {
    const [h, d] = result;
    const stepsCount = Number(steps);
    switch(direction) {
      case 'forward':
        result = [h + stepsCount, d];
        break;
      case 'down':
        result = [h, d - stepsCount];
        break;
      case 'up':
        result = [h, d + stepsCount];
        break;
      default:
        break;
    }
  });
  return result;
};

const multiply = (d: number[]) => d.reduce((acc, cur) => acc * cur, 1);

console.log('first answer:', Math.abs(multiply(getPosition(data))));
