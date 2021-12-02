const inputFilename = "input";
const rawData = await Deno.readTextFile(inputFilename);
const data: number[] = rawData
  .split(/\r?\n/)
  .map((d) => Number(d));

const getIncreasedCound = (measurments: number[]): number => measurments
  .reduce((accumulator, current, index, array) => {
    if (!index) {
      return accumulator;
    }
    if (current > array[index - 1]) {
      return ++accumulator;
    }
    return accumulator;
  }, 0);

const getSum = (measurments: number[]): number => measurments
  .reduce((accumulator, current) => accumulator + current, 0);

const getThreeMeasurments = (measurments: number[]): number[] => measurments
  .reduce((accumulator: number[], current: number, index: number, array: number[]) => ([
    ...accumulator,
    getSum(array.slice(index, index + 3)),
  ]), []);

const firstAnswer = getIncreasedCound(data);
const secondAnswer = getIncreasedCound(getThreeMeasurments(data));
console.log('first answer: ', firstAnswer);
console.log('second answer: ', secondAnswer);
