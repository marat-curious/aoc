import { createReadStream } from 'node:fs';
import { Locations } from './locations.js';

const stream = createReadStream('../input');

const locations = new Locations();

stream.on('data', (chunk) => {
  chunk.toString().split('\n').forEach((c) => {
    if (c.length === 0) {
      return;
    }
    locations.fill(c.split('   ').map((n: string) => n.length > 0 ? parseInt(n) : 0) as [number, number]);
  });
});

stream.on('end', () => {
  const distance = locations.getDistance();
  console.log('Distance: ', distance);
});
