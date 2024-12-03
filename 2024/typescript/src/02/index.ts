import { createReadStream } from 'node:fs';
import { Solution } from './solution.js';

const stream = createReadStream('./sample');

const solution = new Solution();

stream.on('data', (chunk) => {
  chunk.toString().split('\n').forEach((c) => {
    if (c.length === 0) {
      return;
    }
    solution.check(c.split(' ').map((n: string) => parseInt(n)));
  });
});

stream.on('end', () => {
  solution.answer();
});
