import { TestBed } from '@angular/core/testing';

import { CoprasService } from './copras.service';

describe('CoprasService', () => {
  let service: CoprasService;

  beforeEach(() => {
    TestBed.configureTestingModule({});
    service = TestBed.inject(CoprasService);
  });

  it('should be created', () => {
    expect(service).toBeTruthy();
  });
});
