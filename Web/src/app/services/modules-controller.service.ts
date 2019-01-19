import { Injectable } from '@angular/core';

export enum Module {
  HOME,
  STRATGY,
  KNOWLEDGE
}

@Injectable()
export class ModulesControllerService {
  public static active: Module = Module.HOME;

  constructor() { }
}
