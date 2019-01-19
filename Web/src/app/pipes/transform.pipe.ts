import {Pipe, PipeTransform} from '@angular/core';

@Pipe({
  name: 'transform'
})
export class TransformPipe implements PipeTransform {

  transform(items: any[], type: string, ...args: any[]): any {
    if (type === "forEach")
      return items.forEach(args[0]);
    if (type === "filter")
      return items.filter(args[0]);
    if (type === "map")
      return items.map(args[0]);
    if (type === "until")
      return items.filter((value, index) => index < args[0]);
    if (type === "range")
      return items.filter((value, index) => index >= args[0] && index < args[1]);
  }

}
