import {Injectable} from "@angular/core";
import {StrategyModule} from "./strategy/strategy.module";
import {KnowledgeModule} from "./knowledge/knowledge.module";

export class Module {
  constructor(public readonly name: string,
              public readonly color: string) {}
}

/**
 * This is class for managing cross-modules logic
 */
@Injectable()
export class ModulesService {
  readonly modules = {
    home: new Module("Home", "#ffffffc0"),
    knowledge: new Module("Knowledge", "#7a00ffc0"),
    strategy: new Module("Strategy", "#ff117ec0"),

  };


  /**
   * Return modules as array
   */
  get modulesAsArray() {
    return Object.values(this.modules);
  }

  currentModule: Module = this.modules.strategy;

  constructor(public readonly knowledge: KnowledgeModule,
              public readonly strategy: StrategyModule) {}
}
