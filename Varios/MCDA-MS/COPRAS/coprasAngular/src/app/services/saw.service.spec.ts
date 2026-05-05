import { TestBed } from '@angular/core/testing';

import { SawService } from './saw.service';

describe('SawService', () => {
  let service: SawService;

  beforeEach(() => {
    TestBed.configureTestingModule({});
    service = TestBed.inject(SawService);
  });

  it('should be created', () => {
    expect(service).toBeTruthy();
  });
});
